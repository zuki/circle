//
// synchronize64.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2020  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_synchronize64_h
#define _circle_synchronize64_h

#ifndef _circle_synchronize_h
    #error Do not include this header file directly!
#endif

#include <circle/macros.h>
#include <circle/types.h>

#ifdef __cplusplus
extern "C" {
#endif

//
// Execution levels
//
#define TASK_LEVEL      0        // IRQs と FIQs が有効
#define IRQ_LEVEL       1        // IRQsは無効、FIQsは有効
#define FIQ_LEVEL       2        // IRQs と FIQs が無効

unsigned CurrentExecutionLevel (void);

//
// 割り込み制御
//
#define    EnableIRQs()         asm volatile ("msr DAIFClr, #2")
#define    DisableIRQs()        asm volatile ("msr DAIFSet, #2")
#define    EnableInterrupts()   EnableIRQs()            // deprecated
#define    DisableInterrupts()  DisableIRQs()           // deprecated

#define    EnableFIQs()         asm volatile ("msr DAIFClr, #1")
#define    DisableFIQs()        asm volatile ("msr DAIFSet, #1")

// EnterCritical()はnTargetLevelが同じか大きいネストは可能
void EnterCritical (unsigned nTargetLevel = IRQ_LEVEL);
void LeaveCritical (void);

//
// キャッシュ制御
//
#define DATA_CACHE_LINE_LENGTH_MIN      64    // CTR_EL0から
#define DATA_CACHE_LINE_LENGTH_MAX      64

#define InvalidateInstructionCache()    asm volatile ("ic iallu" ::: "memory")
#define FlushPrefetchBuffer()           asm volatile ("isb" ::: "memory")

// 注: データキャッシュの操作にはDataSyncBarrierを含む
void InvalidateDataCache (void) MAXOPT;
void InvalidateDataCacheL1Only (void) MAXOPT;
void CleanDataCache (void) MAXOPT;

void InvalidateDataCacheRange (u64 nAddress, u64 nLength) MAXOPT;
void CleanDataCacheRange (u64 nAddress, u64 nLength) MAXOPT;
void CleanAndInvalidateDataCacheRange (u64 nAddress, u64 nLength) MAXOPT;

void SyncDataAndInstructionCache (void);

//
// キャッシュアライメント
//
#define CACHE_ALIGN                     ALIGN (DATA_CACHE_LINE_LENGTH_MAX)

#define CACHE_ALIGN_SIZE(type, num)     (((  ((num)*sizeof (type) - 1)        \
                            | (DATA_CACHE_LINE_LENGTH_MAX-1)    \
                        ) + 1) / sizeof (type))

#define IS_CACHE_ALIGNED(ptr, size)     (((uintptr) (ptr) & (DATA_CACHE_LINE_LENGTH_MAX-1)) == 0 \
                        && ((size) & (DATA_CACHE_LINE_LENGTH_MAX-1)) == 0)

#define DMA_BUFFER(type, name, num)     type name[CACHE_ALIGN_SIZE (type, num)] CACHE_ALIGN

//
// バリア
//
#define DataSyncBarrier()           asm volatile ("dsb sy" ::: "memory")
#define DataMemBarrier()            asm volatile ("dmb sy" ::: "memory")

#define InstructionSyncBarrier()    asm volatile ("isb" ::: "memory")
#define InstructionMemBarrier()     asm volatile ("isb" ::: "memory")

#define CompilerBarrier()           asm volatile ("" ::: "memory")

#define PeripheralEntry()           ((void) 0)    // ここでは無視
#define PeripheralExit()            ((void) 0)

//
// 割り込みとイベントを待つ
//
#define WaitForInterrupt()          asm volatile ("wfi")
#define WaitForEvent()              asm volatile ("wfe")
#define SendEvent()                 asm volatile ("sev")

#ifdef __cplusplus
}
#endif

#endif
