//
// mutex.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2021  R. Stange <rsta2@o2online.de>
//
// This class was developed by:
//    Brad Robinson <contact@toptensoftware.com>
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
#ifndef _circle_sched_mutex_h
#define _circle_sched_mutex_h

#include <circle/types.h>
#include <circle/sched/synchronizationevent.h>

class CTask;

class CMutex    /// タスク間の相互排除（クリティカルセクション）を提供する方法を提供する
{
public:
    CMutex (void);
    ~CMutex (void);

    /// \brief mutexを取得する。他のタスクがすでにmutexを獲得している場合、タスクをブロックする
    /// \note このミューテックスは同じタスクが複数回取得することが可能
    void Acquire (void);

    /// \brief mutexを開放する。このmutexを待っている他のタスクを起床させる
    void Release (void);

private:
    CTask* m_pOwningTask;       ///< 所有しているタスク
    int m_iReentrancyCount;     ///< リエントラント回数
    CSynchronizationEvent m_event;  ///< イベント
};

#endif
