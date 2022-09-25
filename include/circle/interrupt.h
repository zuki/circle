//
// interrupt.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2019  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_interrupt_h
#define _circle_interrupt_h

#include <circle/bcm2835int.h>
#include <circle/exceptionstub.h>
#include <circle/types.h>

typedef void TIRQHandler (void *pParam);

/// @brief 割り込みシステムクラス
class CInterruptSystem
{
public:
    /// @brief コンストラクタ
    CInterruptSystem (void);
    /// @brief デストラクタ
    ~CInterruptSystem (void);
    /// @brief 初期関数
    /// @return 常にTRUE
    boolean Initialize (void);
    /// @brief 割り込みを設定
    /// @param nIRQ 割り込み番号
    /// @param pHandler 割り込みハンドラ
    /// @param pParam 割り込みハンドラに渡すパラメタ
    void ConnectIRQ (unsigned nIRQ, TIRQHandler *pHandler, void *pParam);
    /// @brief 割り込みを削除
    /// @param nIRQ 割り込み番号
    void DisconnectIRQ (unsigned nIRQ);
    /// @brief 高速割り込みを設定
    /// @param nFIQ 高速割り込み番号
    /// @param pHandler 高速割り込みハンドラ
    /// @param pParam 高速割り込みハンドラに渡すパラメタ
    void ConnectFIQ (unsigned nFIQ, TFIQHandler *pHandler, void *pParam);
    /// @brief 高速割り込みを削除
    void DisconnectFIQ (void);
    /// @brief 割り込みを有効化
    /// @param nIRQ 割り込み番号
    static void EnableIRQ (unsigned nIRQ);
    /// @brief 割り込みを無効化
    /// @param nIRQ 割り込み番号
    static void DisableIRQ (unsigned nIRQ);
    /// @brief 高速割り込みを有効化
    /// @param nFIQ 高速割り込み番号
    static void EnableFIQ (unsigned nFIQ);
    /// @brief 高速割り込みを無効化
    static void DisableFIQ (void);
    /// @brief 割り込みシステムオブジェクトを取得する
    /// @return 割り込みシステムオブジェクト
    static CInterruptSystem *Get (void);
    /// @brief 割り込みハンドラを呼び出す
    static void InterruptHandler (void);

#if RASPPI >= 4
    static void InitializeSecondary (void);

    static void SendIPI (unsigned nCore, unsigned nIPI);

    static void CallSecureMonitor (u32 nFunction, u32 nParam);
    static void SecureMonitorHandler (u32 nFunction, u32 nParam);
#endif

private:
    /// @brief 割り込みハンドラを実行する
    /// @param nIRQ 割り込み番号
    /// @return 実行した場合はTRUE、ハンドラが設定されていなかったらFALSE
    boolean CallIRQHandler (unsigned nIRQ);

private:
    /// @brief 割り込みハンドラの配列
    TIRQHandler *m_apIRQHandler[IRQ_LINES];
    /// @brief 割り込みハンドラに渡すパラメタの配列
    void        *m_pParam[IRQ_LINES];
    /// @brief 唯一のこのオブジェクト
    static CInterruptSystem *s_pThis;
};

#endif
