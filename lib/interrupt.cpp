//
// interrupt.cpp
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
#include <circle/interrupt.h>
#include <circle/synchronize.h>
#include <circle/multicore.h>
#include <circle/bcm2835.h>
#include <circle/bcm2836.h>
#include <circle/memio.h>
#include <circle/sysconfig.h>
#include <circle/types.h>
#include <assert.h>

#define ARM_IC_IRQ_REGS        3

// 保留(0x3F0B200/8): 0-31: IRQ1,  32-63: IRQ2, 64-: 基本
#define ARM_IC_IRQ_PENDING(irq)    (  (irq) < ARM_IRQ2_BASE    \
                ? ARM_IC_IRQ_PENDING_1        \
                : ((irq) < ARM_IRQBASIC_BASE    \
                    ? ARM_IC_IRQ_PENDING_2    \
                    : ARM_IC_IRQ_BASIC_PENDING))
// イネーブル(0x3F0B210/8): 0-31: RQ1, 32-63: IRQ2, 64-: 基本
#define ARM_IC_IRQS_ENABLE(irq)    (  (irq) < ARM_IRQ2_BASE    \
                ? ARM_IC_ENABLE_IRQS_1        \
                : ((irq) < ARM_IRQBASIC_BASE    \
                    ? ARM_IC_ENABLE_IRQS_2    \
                    : ARM_IC_ENABLE_BASIC_IRQS))
// ディスエーブル(0x3F0B21C/220/4): 0-31: IRQ1, 32-63: IRQ2, 64-: 基本
#define ARM_IC_IRQS_DISABLE(irq) (  (irq) < ARM_IRQ2_BASE    \
                ? ARM_IC_DISABLE_IRQS_1    \
                : ((irq) < ARM_IRQBASIC_BASE    \
                    ? ARM_IC_DISABLE_IRQS_2    \
                    : ARM_IC_DISABLE_BASIC_IRQS))
// 1 << (irq & 0x1F) : 0x00-0x1F, 0x20-0x3F : 0x40-
#define ARM_IRQ_MASK(irq)    (1 << ((irq) & (ARM_IRQS_PER_REG-1)))

// 割り込みシステムはシステムに一つ
CInterruptSystem *CInterruptSystem::s_pThis = 0;

CInterruptSystem::CInterruptSystem (void)
{
    for (unsigned nIRQ = 0; nIRQ < IRQ_LINES; nIRQ++) // IRQ_LINES=84
    {
        m_apIRQHandler[nIRQ] = 0;
        m_pParam[nIRQ] = 0;
    }

    s_pThis = this;
}

CInterruptSystem::~CInterruptSystem (void)
{
    DisableIRQs ();

    PeripheralEntry ();

    // FIQを無効
    write32 (ARM_IC_FIQ_CONTROL, 0);    // 0x3F00B20C
    // 基本、IRQ1, IRQ2をdisable
    write32 (ARM_IC_DISABLE_IRQS_1, (u32) -1);
    write32 (ARM_IC_DISABLE_IRQS_2, (u32) -1);
    write32 (ARM_IC_DISABLE_BASIC_IRQS, (u32) -1);

// 0x4000_0040: コア0のタイマー割り込み制御レジスタ
#if RASPPI >= 2
    write32 (ARM_LOCAL_TIMER_INT_CONTROL0, 0);
#endif

    PeripheralExit ();

    s_pThis = 0;
}

boolean CInterruptSystem::Initialize (void)
{
#if AARCH == 32
    TExceptionTable *pTable = (TExceptionTable *) ARM_EXCEPTION_TABLE_BASE;
    pTable->IRQ = ARM_OPCODE_BRANCH (ARM_DISTANCE (pTable->IRQ, IRQStub));
#ifndef USE_RPI_STUB_AT
    pTable->FIQ = ARM_OPCODE_BRANCH (ARM_DISTANCE (pTable->FIQ, FIQStub));
#endif

    SyncDataAndInstructionCache ();
#endif

// 該当する（AARCH=64）
#ifndef USE_RPI_STUB_AT
    PeripheralEntry ();
    // FIQを無効に
    write32 (ARM_IC_FIQ_CONTROL, 0);
    // GPU IRQ1とiRQ2、基本IRQのすべてをDisable
    write32 (ARM_IC_DISABLE_IRQS_1, (u32) -1);
    write32 (ARM_IC_DISABLE_IRQS_2, (u32) -1);
    write32 (ARM_IC_DISABLE_BASIC_IRQS, (u32) -1);

// コア0のタイマー割り込みをすべて無効に
#if RASPPI >= 2
    write32 (ARM_LOCAL_TIMER_INT_CONTROL0, 0);
#endif

    PeripheralExit ();
#endif
    // IRQを有効に(DAIFのIをクリア)
    EnableIRQs ();

    return TRUE;
}

void CInterruptSystem::ConnectIRQ (unsigned nIRQ, TIRQHandler *pHandler, void *pParam)
{
    assert (nIRQ < IRQ_LINES);
    assert (m_apIRQHandler[nIRQ] == 0);
    // ハンドラと引数をセット
    m_apIRQHandler[nIRQ] = pHandler;
    m_pParam[nIRQ] = pParam;
    // 指定の番号の割り込みを有効に
    EnableIRQ (nIRQ);
}

void CInterruptSystem::DisconnectIRQ (unsigned nIRQ)
{
    assert (nIRQ < IRQ_LINES);
    assert (m_apIRQHandler[nIRQ] != 0);

    DisableIRQ (nIRQ);

    m_apIRQHandler[nIRQ] = 0;
    m_pParam[nIRQ] = 0;
}

void CInterruptSystem::ConnectFIQ (unsigned nFIQ, TFIQHandler *pHandler, void *pParam)
{
#ifdef USE_RPI_STUB_AT
    assert (0);
#endif
    assert (nFIQ <= ARM_MAX_FIQ);
    assert (pHandler != 0);
    assert (FIQData.pHandler == 0);
    // FIQDataはexceptionstub64.Sで定義されている
    FIQData.pHandler = pHandler;
    FIQData.pParam = pParam;

    EnableFIQ (nFIQ);
}

void CInterruptSystem::DisconnectFIQ (void)
{
    assert (FIQData.pHandler != 0);

    DisableFIQ ();

    FIQData.pHandler = 0;
    FIQData.pParam = 0;
}

void CInterruptSystem::EnableIRQ (unsigned nIRQ)
{
    PeripheralEntry ();

    assert (nIRQ < IRQ_LINES);
    // nIRQが63以下はBCM2835の割り込みペリフェラルを使用
    if (nIRQ < ARM_IRQLOCAL_BASE)
    {
        write32 (ARM_IC_IRQS_ENABLE (nIRQ), ARM_IRQ_MASK (nIRQ));
    }
    else    // 64以上はローカルARMペリフェラルで、このうち、
    {       // Core0の非セキュアな物理カウンタ(CNTPNS)によるタイマー割り込みのみ実装
#if RASPPI >= 2
        assert (nIRQ == ARM_IRQLOCAL0_CNTPNS);  // 現在はコア0タイマーのCNTPNSIRQ
        write32 (ARM_LOCAL_TIMER_INT_CONTROL0,  // だけ実装。この割り込みを有効に
             read32 (ARM_LOCAL_TIMER_INT_CONTROL0) | (1 << 1)); // 1: CNTPNSIRQ
#else
        assert (0);
#endif
    }

    PeripheralExit ();
}

void CInterruptSystem::DisableIRQ (unsigned nIRQ)
{
    PeripheralEntry ();

    assert (nIRQ < IRQ_LINES);

    if (nIRQ < ARM_IRQLOCAL_BASE)
    {
        write32 (ARM_IC_IRQS_DISABLE (nIRQ), ARM_IRQ_MASK (nIRQ));
    }
    else
    {
#if RASPPI >= 2
        assert (nIRQ == ARM_IRQLOCAL0_CNTPNS);    // the only implemented local IRQ so far
        write32 (ARM_LOCAL_TIMER_INT_CONTROL0,
             read32 (ARM_LOCAL_TIMER_INT_CONTROL0) & ~(1 << 1));
#else
        assert (0);
#endif
    }

    PeripheralExit ();
}

void CInterruptSystem::EnableFIQ (unsigned nFIQ)
{
    PeripheralEntry ();
    // ARM_MAX_FIQ = 71: FIQには基本IRQはない
    assert (nFIQ <= ARM_MAX_FIQ);

    write32 (ARM_IC_FIQ_CONTROL, nFIQ | 0x80);

    PeripheralExit ();
}

void CInterruptSystem::DisableFIQ (void)
{
    PeripheralEntry ();

    write32 (ARM_IC_FIQ_CONTROL, 0);

    PeripheralExit ();
}

CInterruptSystem *CInterruptSystem::Get (void)
{
    assert (s_pThis != 0);
    return s_pThis;
}

boolean CInterruptSystem::CallIRQHandler (unsigned nIRQ)
{
    assert (nIRQ < IRQ_LINES);
    TIRQHandler *pHandler = m_apIRQHandler[nIRQ];

    if (pHandler != 0)
    {
        (*pHandler) (m_pParam[nIRQ]);

        return TRUE;
    }
    else
    {
        DisableIRQ (nIRQ);
    }

    return FALSE;
}

void CInterruptSystem::InterruptHandler (void)
{
    assert (s_pThis != 0);

#if RASPPI >= 2
    // コア0の割り込み要因を取得
    u32 nLocalPending = read32 (ARM_LOCAL_IRQ_PENDING0);
    // 1. CNTPNS, 2. mailbox0-3, 3. GPU以外はエラー(ローカルタイマー(11)は未使用)
    assert (!(nLocalPending & ~(1 << 1 | 0xF << 4 | 1 << 8)));
    // 1. 物理カウンタによる割り込み（IRQ割り込みはこれだけ実装）
    if (nLocalPending & (1 << 1))
    {
        s_pThis->CallIRQHandler (ARM_IRQLOCAL0_CNTPNS);

        return;
    }
#endif

#ifdef ARM_ALLOW_MULTI_CORE
    // 2. コアの停止処理のみ実装している。それ以外はfalseが返る
    if (CMultiCoreSupport::LocalInterruptHandler ())
    {
        return;
    }
#endif

    PeripheralEntry ();
    // 3. GPU割り込み
    u32 Pending[ARM_IC_IRQ_REGS];
    Pending[0] = read32 (ARM_IC_IRQ_PENDING_1);
    Pending[1] = read32 (ARM_IC_IRQ_PENDING_2);
    Pending[2] = read32 (ARM_IC_IRQ_BASIC_PENDING) & 0xFF;  // ARM固有割り込みのみ

    PeripheralExit ();

    // 保留ビットが立っている最初の割り込みのハンドラをコールする
    for (unsigned nReg = 0; nReg < ARM_IC_IRQ_REGS; nReg++)
    {
        u32 nPending = Pending[nReg];
        if (nPending != 0)
        {
            unsigned nIRQ = nReg * ARM_IRQS_PER_REG;
            // bit 0からビットが立っているソースのハンドラを呼び出す
            do
            {
                if (   (nPending & 1)
                    && s_pThis->CallIRQHandler (nIRQ))
                {
                    return;     // 一つ呼び出しが成功したら終了
                }

                nPending >>= 1;
                nIRQ++;
            }
            while (nPending != 0);
        }
    }
}

void InterruptHandler (void)
{
    PeripheralExit ();    // exit from interrupted peripheral

    CInterruptSystem::InterruptHandler ();

    PeripheralEntry ();    // continuing with interrupted peripheral
}
