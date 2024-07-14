//
// synchronize64.cpp
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2021  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <circle/synchronize.h>
#include <circle/sysconfig.h>
#include <assert.h>

#define MAX_CRITICAL_LEVEL    20        // maximum nested level of EnterCritical()

unsigned CurrentExecutionLevel (void)
{
    u32 nFlags;
    asm volatile ("mrs %0, daif" : "=r" (nFlags));

    if (nFlags & 0x40)
    {
        return FIQ_LEVEL;
    }

    if (nFlags & 0x80)
    {
        return IRQ_LEVEL;
    }

    return TASK_LEVEL;
}

#ifdef ARM_ALLOW_MULTI_CORE
// マルチコアをサポートする場合はクリティカルレベルの入れ子を保存する配列をコア毎に持つ

static volatile unsigned s_nCriticalLevel[CORES] = {0};
static volatile u32 s_nFlags[CORES][MAX_CRITICAL_LEVEL];

// 対象レベルがタスクレベルでない場合はクリティカルレベルを入れ子にできる
void EnterCritical (unsigned nTargetLevel)
{
    assert (nTargetLevel == IRQ_LEVEL || nTargetLevel == FIQ_LEVEL);

    // 1. コアIDを取得
    u64 nMPIDR;
    asm volatile ("mrs %0, mpidr_el1" : "=r" (nMPIDR));
    unsigned nCore = nMPIDR & (CORES-1);
    // 2. DAIF取得
    u32 nFlags;
    // bit[9:6] = DAIF
    asm volatile ("mrs %0, daif" : "=r" (nFlags));

    // すでにFIQレベルにある場合、ここではIRQ_LEVELには戻らない
    assert (nTargetLevel == FIQ_LEVEL || !(nFlags & 0x40));     // !0x40 = Fがマスクされていない
    // 3. IRQとFIQを無効にする
    asm volatile ("msr DAIFSet, #3");

    assert (s_nCriticalLevel[nCore] < MAX_CRITICAL_LEVEL);
    // 4. IRQとFIQを無効にする前の状態を保存する
    s_nFlags[nCore][s_nCriticalLevel[nCore]++] = nFlags;

    // 5. 対象レベルがIQR_LEVELの場合はFIQを有効にする
    if (nTargetLevel == IRQ_LEVEL)
    {
        EnableFIQs ();
    }
    // 6. データメモリバリア
    DataMemBarrier ();
}

void LeaveCritical (void)
{
    // 1. コアIDを取得
    u64 nMPIDR;
    asm volatile ("mrs %0, mpidr_el1" : "=r" (nMPIDR));
    unsigned nCore = nMPIDR & (CORES-1);
    // 2. データメモリバリア
    DataMemBarrier ();
    // 3. FIQを無効に
    DisableFIQs ();
    // 4. IRQとFIQを無効にする前の状態を復元する
    assert (s_nCriticalLevel[nCore] > 0);
    u32 nFlags = s_nFlags[nCore][--s_nCriticalLevel[nCore]];
    asm volatile ("msr daif, %0" :: "r" (nFlags));
}

#else
// シングルコアの場合はクリティカルレベルの入れ子を保存する配列は1つだけ

static volatile unsigned s_nCriticalLevel = 0;
static volatile u32 s_nFlags[MAX_CRITICAL_LEVEL];

void EnterCritical (unsigned nTargetLevel)
{
    assert (nTargetLevel == IRQ_LEVEL || nTargetLevel == FIQ_LEVEL);

    u32 nFlags;
    asm volatile ("mrs %0, daif" : "=r" (nFlags));

    // if we are already on FIQ_LEVEL, we must not go back to IRQ_LEVEL here
    assert (nTargetLevel == FIQ_LEVEL || !(nFlags & 0x40));

    asm volatile ("msr DAIFSet, #3");    // disable both IRQ and FIQ

    assert (s_nCriticalLevel < MAX_CRITICAL_LEVEL);
    s_nFlags[s_nCriticalLevel++] = nFlags;

    if (nTargetLevel == IRQ_LEVEL)
    {
        EnableFIQs ();
    }

    DataMemBarrier ();
}

void LeaveCritical (void)
{
    DataMemBarrier ();

    DisableFIQs ();

    assert (s_nCriticalLevel > 0);
    u32 nFlags = s_nFlags[--s_nCriticalLevel];

    asm volatile ("msr daif, %0" :: "r" (nFlags));
}

#endif

//
// ARMv8-Aのキャッシュ管理操作
//
// 注: 以下の関数はすべての変数をCPUレジスタに保持しなければならない。
//     現在のところ、これは最大限の最適化でも保証される (see circle/synchronize64.h).
//
//     以下の数値は、CTR_EL0、CSSELR_EL1、CCSIDR_EL1、CLIDR_EL1を使って（動的に）
//     決定できる。BCM2837/BCM2711のCortex-A53/A72実装を使用する限り、これらの
//     静的な値は機能する:
//

#if RASPPI == 3

#define SETWAY_LEVEL_SHIFT        1

#define L1_DATA_CACHE_SETS        128
#define L1_DATA_CACHE_WAYS        4
    #define L1_SETWAY_WAY_SHIFT        30    // 32-Log2(L1_DATA_CACHE_WAYS)
#define L1_DATA_CACHE_LINE_LENGTH    64
    #define L1_SETWAY_SET_SHIFT        6    // Log2(L1_DATA_CACHE_LINE_LENGTH)

#define L2_CACHE_SETS            512
#define L2_CACHE_WAYS            16
    #define L2_SETWAY_WAY_SHIFT        28    // 32-Log2(L2_CACHE_WAYS)
#define L2_CACHE_LINE_LENGTH        64
    #define L2_SETWAY_SET_SHIFT        6    // Log2(L2_CACHE_LINE_LENGTH)

#else

#define SETWAY_LEVEL_SHIFT        1

#define L1_DATA_CACHE_SETS        256
#define L1_DATA_CACHE_WAYS        2
    #define L1_SETWAY_WAY_SHIFT        31    // 32-Log2(L1_DATA_CACHE_WAYS)
#define L1_DATA_CACHE_LINE_LENGTH    64
    #define L1_SETWAY_SET_SHIFT        6    // Log2(L1_DATA_CACHE_LINE_LENGTH)

#define L2_CACHE_SETS            1024
#define L2_CACHE_WAYS            16
    #define L2_SETWAY_WAY_SHIFT        28    // 32-Log2(L2_CACHE_WAYS)
#define L2_CACHE_LINE_LENGTH        64
    #define L2_SETWAY_SET_SHIFT        6    // Log2(L2_CACHE_LINE_LENGTH)

#endif

void InvalidateDataCache (void)
{
    // invalidate L1 data cache
    for (unsigned nSet = 0; nSet < L1_DATA_CACHE_SETS; nSet++)
    {
        for (unsigned nWay = 0; nWay < L1_DATA_CACHE_WAYS; nWay++)
        {
            u64 nSetWayLevel =   nWay << L1_SETWAY_WAY_SHIFT
                       | nSet << L1_SETWAY_SET_SHIFT
                       | 0 << SETWAY_LEVEL_SHIFT;

            asm volatile ("dc isw, %0" : : "r" (nSetWayLevel) : "memory");
        }
    }

    // invalidate L2 unified cache
    for (unsigned nSet = 0; nSet < L2_CACHE_SETS; nSet++)
    {
        for (unsigned nWay = 0; nWay < L2_CACHE_WAYS; nWay++)
        {
            u64 nSetWayLevel =   nWay << L2_SETWAY_WAY_SHIFT
                       | nSet << L2_SETWAY_SET_SHIFT
                       | 1 << SETWAY_LEVEL_SHIFT;

            asm volatile ("dc isw, %0" : : "r" (nSetWayLevel) : "memory");
        }
    }

    DataSyncBarrier ();
}

void InvalidateDataCacheL1Only (void)
{
    // invalidate L1 data cache
    for (unsigned nSet = 0; nSet < L1_DATA_CACHE_SETS; nSet++)
    {
        for (unsigned nWay = 0; nWay < L1_DATA_CACHE_WAYS; nWay++)
        {
            u64 nSetWayLevel =   nWay << L1_SETWAY_WAY_SHIFT
                       | nSet << L1_SETWAY_SET_SHIFT
                       | 0 << SETWAY_LEVEL_SHIFT;

            asm volatile ("dc isw, %0" : : "r" (nSetWayLevel) : "memory");
        }
    }

    DataSyncBarrier ();
}

void CleanDataCache (void)
{
    // clean L1 data cache
    for (unsigned nSet = 0; nSet < L1_DATA_CACHE_SETS; nSet++)
    {
        for (unsigned nWay = 0; nWay < L1_DATA_CACHE_WAYS; nWay++)
        {
            u64 nSetWayLevel =   nWay << L1_SETWAY_WAY_SHIFT
                       | nSet << L1_SETWAY_SET_SHIFT
                       | 0 << SETWAY_LEVEL_SHIFT;

            asm volatile ("dc csw, %0" : : "r" (nSetWayLevel) : "memory");
        }
    }

    // clean L2 unified cache
    for (unsigned nSet = 0; nSet < L2_CACHE_SETS; nSet++)
    {
        for (unsigned nWay = 0; nWay < L2_CACHE_WAYS; nWay++)
        {
            u64 nSetWayLevel =   nWay << L2_SETWAY_WAY_SHIFT
                       | nSet << L2_SETWAY_SET_SHIFT
                       | 1 << SETWAY_LEVEL_SHIFT;

            asm volatile ("dc csw, %0" : : "r" (nSetWayLevel) : "memory");
        }
    }

    DataSyncBarrier ();
}

void InvalidateDataCacheRange (u64 nAddress, u64 nLength)
{
    while (1)
    {
        asm volatile ("dc ivac, %0" : : "r" (nAddress) : "memory");

        if (nLength <= DATA_CACHE_LINE_LENGTH_MIN)
        {
            break;
        }

        nAddress += DATA_CACHE_LINE_LENGTH_MIN;
        nLength  -= DATA_CACHE_LINE_LENGTH_MIN;
    }

    DataSyncBarrier ();
}

void CleanDataCacheRange (u64 nAddress, u64 nLength)
{
    while (1)
    {
        asm volatile ("dc cvac, %0" : : "r" (nAddress) : "memory");

        if (nLength <= DATA_CACHE_LINE_LENGTH_MIN)
        {
            break;
        }

        nAddress += DATA_CACHE_LINE_LENGTH_MIN;
        nLength  -= DATA_CACHE_LINE_LENGTH_MIN;
    }

    DataSyncBarrier ();
}

void CleanAndInvalidateDataCacheRange (u64 nAddress, u64 nLength)
{
    while (1)
    {
        asm volatile ("dc civac, %0" : : "r" (nAddress) : "memory");

        if (nLength <= DATA_CACHE_LINE_LENGTH_MIN)
        {
            break;
        }

        nAddress += DATA_CACHE_LINE_LENGTH_MIN;
        nLength  -= DATA_CACHE_LINE_LENGTH_MIN;
    }

    DataSyncBarrier ();
}

void SyncDataAndInstructionCache (void)
{
    CleanDataCache ();
    //DataSyncBarrier ();        // included in CleanDataCache()

    InvalidateInstructionCache ();
    DataSyncBarrier ();

    InstructionSyncBarrier ();
}
