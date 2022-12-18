//
// semaphore.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2021  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_sched_semaphore_h
#define _circle_sched_semaphore_h

#include <circle/sched/synchronizationevent.h>
#include <circle/types.h>

class CSemaphore    /// セマフォ動機クラスを実装する
{
public:
    /// \param nInitialCount セマフォの初期カウント
    CSemaphore (unsigned nInitialCount = 1);

    ~CSemaphore (void);

    /// \return 現在のセマフォカウント
    unsigned GetState (void) const;

    /// \brief セマフォカウントをデクリメントする; カウントがすでに0の場合はタスクをブロックする
    void Down (void);

    /// \brief セマフォカウントをインクリメントする; カウントが0の場合は他の待機タスクを起床させる
    /// \note 割り込みコンテキストから呼び出し可能
    void Up (void);

    /// \brief セマフォカウントのデクリメントを試みる
    /// \return 操作は成功したか?
    boolean TryDown (void);

private:
    volatile int m_nCount;          ///< カウント

    CSynchronizationEvent m_Event;  ///< イベント
};

#endif
