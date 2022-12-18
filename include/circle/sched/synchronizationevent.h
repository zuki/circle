//
// synchronizationevent.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2021  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_sched_synchronizationevent_h
#define _circle_sched_synchronizationevent_h

#include <circle/types.h>

class CTask;

class CSynchronizationEvent /// タスクの実行とイベントを同期させるメソッドを提供する
{
public:
    /// \param bState イベントの初期状態（デフォルトはクリア）
    CSynchronizationEvent (boolean bState = FALSE);

    ~CSynchronizationEvent (void);

    /// \return イベントはあるか?
    boolean GetState (void);

    /// \brief イベントをクリアする
    void Clear (void);
    /// \brief イベントをセットする; 現在このイベントを待っているすべてのタスクを起床させる
    /// \note 割り込みコンテキストから呼び出し可能
    void Set (void);

    /// \brief イベントがクリアされている場合、呼び出し元のタスクをブロックする
    /// \note 後でイベントがセットされるとタスクは起床する
    /// \note 複数のタスクがイベントがセットされるのを待つことができる
    void Wait (void);

    /// \brief このイベントがセットされるか、指定の時間が経過するまで待つ
    /// \param nMicroSeconds マイクロ秒単位のタイムアウト
    /// \return タイムアウトの場合TRUE
    /// \note メソッドがリターンした原因を調べるには、GetState() を使用して\n
    ///     イベントが設定されているかどうかを確認する。
    /// \note タイムアウトが発生しても、イベントが設定されている可能性がある
    boolean WaitWithTimeout (unsigned nMicroSeconds);

private:
    void Pulse (void);    // 実際にイベントセットすることなくすべてのタスクを起床させる
    friend class CMutex;

private:
    volatile boolean m_bState;      ///< イベント
    CTask    *m_pWaitListHead;      ///< 待機タスク用のリンクリスト
};

#endif
