//
// multicore.cpp
//
// Some information in this file is taken from Linux and is:
//    Copyright (C) Broadcom
//    Licensed under GPL2
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2022  R. Stange <rsta2@o2online.de>
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
#include <circle/multicore.h>

#ifdef ARM_ALLOW_MULTI_CORE

#include <circle/startup.h>
#include <circle/bcm2836.h>
#include <circle/interrupt.h>
#include <circle/timer.h>
#include <circle/logger.h>
#include <circle/memio.h>
#include <circle/synchronize.h>
#include <assert.h>

static const char FromMultiCore[] = "mcore";

/// @brief マルチサポートオブジェクト（シングルトン）
CMultiCoreSupport *CMultiCoreSupport::s_pThis = 0;

/// @brief コンストラクタ. シングルトンにオブジェクトをセット
/// @param pMemorySystem メモリシステムオブジェクト
CMultiCoreSupport::CMultiCoreSupport (CMemorySystem *pMemorySystem)
:    m_pMemorySystem (pMemorySystem)
{
    assert (s_pThis == 0);
    s_pThis = this;
}

CMultiCoreSupport::~CMultiCoreSupport (void)
{
    m_pMemorySystem = 0;

    s_pThis = 0;
}

/// @brief 初期化関数
/// @return 処理の成否を返す
boolean CMultiCoreSupport::Initialize (void)
{
#if RASPPI <= 3
    // 1. IRQとFIQをコア0にルーティング
    u32 nRouting = read32 (ARM_LOCAL_GPU_INT_ROUTING);
    nRouting &= ~0x0F;      // [3:2] = 0, [1:0] = 0: IRQとFIQをコア0にルーティング
    write32 (ARM_LOCAL_GPU_INT_ROUTING, nRouting);
    // 2. コア0でmailbox-0のIRQ割り込みを有効に
    write32 (ARM_LOCAL_MAILBOX_INT_CONTROL0, 1);
#endif

    CleanDataCache ();    // セカンダリコアからアクセスできるように全データを書き出す

    for (unsigned nCore = 1; nCore < CORES; nCore++)
    {
#if AARCH == 32
        u32 nMailBoxClear = ARM_LOCAL_MAILBOX3_CLR0 + 0x10 * nCore;

        DataSyncBarrier ();
#else
        TSpinTable *pSpinTable = (TSpinTable *) ARM_SPIN_TABLE_BASE;    // 0x000000D8
#endif

        unsigned nTimeout = 100;
#if AARCH == 32
        while (read32 (nMailBoxClear) != 0)
#else
        while (pSpinTable->SpinCore[nCore] != 0)
#endif
        {
            if (--nTimeout == 0)
            {
                CLogger::Get ()->Write (FromMultiCore, LogError, "CPU core %u does not respond", nCore);

                return FALSE;
            }

            CTimer::SimpleMsDelay (1);
        }

#if AARCH == 32
        write32 (ARM_LOCAL_MAILBOX3_SET0 + 0x10 * nCore, (u32) &_start_secondary);
#else
        pSpinTable->SpinCore[nCore] = (uintptr) &_start_secondary;
        // TODO: CleanDataCacheRange ((u64) pSpinTable, sizeof *pSpinTable);
        CleanDataCache ();
#endif

        nTimeout = 500;
        do
        {
            asm volatile ("sev");

            if (--nTimeout == 0)
            {
                CLogger::Get ()->Write (FromMultiCore, LogError, "CPU core %u did not start", nCore);

                return FALSE;
            }

            CTimer::SimpleMsDelay (1);

            DataMemBarrier ();
        }
#if AARCH == 32
        while (read32 (nMailBoxClear) != 0);
#else
        while (pSpinTable->SpinCore[nCore] != 0);
#endif
    }

    return TRUE;
}

void CMultiCoreSupport::IPIHandler (unsigned nCore, unsigned nIPI)
{
    assert (nCore < CORES);
    assert (nIPI <= IPI_MAX);

    // 処理内容が対象のコアを停止するだった場合
    if (nIPI == IPI_HALT_CORE)
    {
        CLogger::Get ()->Write (FromMultiCore, LogDebug, "CPU core %u will halt now", nCore);

        halt ();
    }
}

void CMultiCoreSupport::SendIPI (unsigned nCore, unsigned nIPI)
{
    assert (nCore < CORES);
    assert (nIPI <= IPI_MAX);

#if RASPPI <= 3
    write32 (ARM_LOCAL_MAILBOX0_SET0 + 0x10 * nCore, 1 << nIPI);
#else
    CInterruptSystem::SendIPI (nCore, nIPI);
#endif
}

void CMultiCoreSupport::HaltAll (void)
{
    for (unsigned nCore = 0; nCore < CORES; nCore++)
    {
        if (ThisCore () != nCore)
        {
            SendIPI (nCore, IPI_HALT_CORE);
        }
    }

    halt ();
}

#if RASPPI <= 3

boolean CMultiCoreSupport::LocalInterruptHandler (void)
{
    if (s_pThis == 0)
    {
        return FALSE;
    }

    unsigned nCore = ThisCore ();
    // 各コアのGPU割り込みでなければ何もしない）
    if (!(read32 (ARM_LOCAL_IRQ_PENDING0 + 4 * nCore) & 0x10))
    {
        return FALSE;
    }

    uintptr nMailBoxClear = ARM_LOCAL_MAILBOX0_CLR0 + 0x10 * nCore;
    // メールボック0が0なら何もしない
    u32 nIPIMask = read32 (nMailBoxClear);
    if (nIPIMask == 0)
    {
        return FALSE;
    }

    // IPI（割り込み内容）を特定する
    unsigned nIPI;
    for (nIPI = 0; !(nIPIMask & 1); nIPI++)
    {
        nIPIMask >>= 1;
    }
    // 特定されたビットをクリアする
    write32 (nMailBoxClear, 1 << nIPI);
    DataSyncBarrier ();
    // nCoreにnIPIを送る
    s_pThis->IPIHandler (nCore, nIPI);

    return TRUE;
}

#else

void CMultiCoreSupport::LocalInterruptHandler (unsigned nFromCore, unsigned nIPI)
{
    if (s_pThis != 0)
    {
        s_pThis->IPIHandler (ThisCore (), nIPI);
    }
}

#endif

/// @brief 2次コアのmainルーチンの処理部
void CMultiCoreSupport::EntrySecondary (void)
{
    assert (s_pThis != 0);

    assert (s_pThis->m_pMemorySystem != 0);
    s_pThis->m_pMemorySystem->InitializeSecondary ();

    unsigned nCore = ThisCore ();
#if AARCH == 32
    write32 (ARM_LOCAL_MAILBOX3_CLR0 + 0x10 * nCore, 0);
#else
    TSpinTable *pSpinTable = (TSpinTable *) ARM_SPIN_TABLE_BASE;
    pSpinTable->SpinCore[nCore] = 0;
    DataSyncBarrier ();
#endif

#if RASPPI <= 3
    /* メールボックスnのIRQを有効にする */
    write32 (ARM_LOCAL_MAILBOX_INT_CONTROL0 + 4 * nCore, 1);
#else
    CInterruptSystem::InitializeSecondary ();
#endif
    EnableIRQs ();

    CLogger::Get ()->Write (FromMultiCore, LogDebug, "CPU core %u started", nCore);

    s_pThis->Run (nCore);

    CLogger::Get ()->Write (FromMultiCore, LogDebug, "CPU core %u will halt now", nCore);
}

/// @brief 2次コア(AP)のmainルーチン
/// @param
void main_secondary (void)
{
    CMultiCoreSupport::EntrySecondary ();
}

#endif
