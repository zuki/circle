//
// usertimer.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2017-2018  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_usertimer_h
#define _circle_usertimer_h

#include <circle/interrupt.h>
#include <circle/types.h>

class CUserTimer;

typedef void TUserTimerHandler (CUserTimer *pUserTimer, void *pParam);

class CUserTimer    /// きめ細かいユーザプログラマブルな割り込みタイマー（ARM_IRQ_TIMER1ベース）
{
public:
    /// \param pInterruptSystem 割り込みシステムオブジェクトへのポインタ
    /// \param pHandler ユーザタイマーハンドラへのポインタ
    /// \param pParam ユーザタイマーハンドラへ渡されるパラメタ
    /// \param bUseFIQ IRQではなくFIQを使用する
    CUserTimer (CInterruptSystem *pInterruptSystem,
            TUserTimerHandler *pHandler, void *pParam = 0,
            boolean bUseFIQ = FALSE);

    ~CUserTimer (void);

    /// \return 操作の成否
    /// \note 1時間後に発火するタイマーが自動的にスタートする
    boolean Initialize (void);

    /// \brief ユーザタイマーを停止する。再度利用する場合は初期化が必要
    void Stop (void);

    /// \param nDelayMicros ユーザタイマーの発火時間（マイクロ秒単位で > 1）
    /// \note 新しい発火時間をセットするにめにユーザタイマーから呼び出される必要がある
    /// \note 実行中のユーザータイマーを新しいディレイで呼び出すことができる
    void Start (unsigned nDelayMicros);
#define USER_CLOCKHZ    1000000U

private:
    /// \breief 割り込みハンドラ
    /// \param ユーザタイマーハンドラへ渡されたパラメタ（CUserTimerへのポインタ）
    static void InterruptHandler (void *pParam);

private:
    CInterruptSystem    *m_pInterruptSystem;    // 割り込みシステムオブジェクトへのポインタ
    TUserTimerHandler   *m_pHandler;            // 割り込みハンドラへのポインタ
    void                *m_pParam;              // ユーザタイマーハンドラへ渡されるパラメタ
    boolean              m_bUseFIQ;             // IRQではなくFIQを使用する

    boolean              m_bInitialized;        // 初期化済みか
};

#endif
