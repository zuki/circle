//
/// \file scheduler.h
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
#ifndef _circle_sched_scheduler_h
#define _circle_sched_scheduler_h

#include <circle/sched/task.h>
#include <circle/spinlock.h>
#include <circle/device.h>
#include <circle/sysconfig.h>
#include <circle/types.h>

typedef void TSchedulerTaskHandler (CTask *pTask);

/// \note このスケジューラは優先順位を持たないラウンドロビン方式を使用する

class CScheduler /// 協調型の非プリエンプティスケジューラ。ある時点でどのタスクが実行するかを制御する
{
public:
    CScheduler (void);
    ~CScheduler (void);

    /// \brief 杉のタスクに切り替える
    /// \note タスクは長い計算をする場合、時折このメソッドを呼び出す必要がある
    void Yield (void);

    /// \param nSeconds 現在のタスクがスリープする秒数
    void Sleep (unsigned nSeconds);
    /// \param nMilliSeconds 現在のタスクがスリープするミリ秒数
    void MsSleep (unsigned nMilliSeconds);
    /// \param nMicroSeconds 現在のタスクがスリープするマイクロ秒数
    void usSleep (unsigned nMicroSeconds);

    /// \return 現在実行中のCTaskオブジェクトへのポインタ
    CTask *GetCurrentTask (void);

    /// \param pTaskName 検索するタスク名
    /// \return 指定した名前を持つCTaskオブジェクトへのポインタ（見つからなかった場合は0）
    CTask *GetTask (const char *pTaskName);

    /// \param pTask 任意のポインタ
    /// \return このポインタは現在知られているタスクのCTaskオブジェクトを参照しているか？
    boolean IsValidTask (CTask *pTask);

    /// \param pHandler タスクスイッチの際に呼び出されるコールバック関数
    /// \note ハンドラは次に制御を取得するタスクのCTaskオブジェクトへのポインタを\n
    ///      引数に呼び出される
    void RegisterTaskSwitchHandler (TSchedulerTaskHandler *pHandler);
    /// \param pHandler タスクが終了する際に呼び出されるコールバック関数
    /// \note ハンドラは終了するタスクのCTaskオブジェクトへのポインタを\n
    ///      引数に呼び出される
    void RegisterTaskTerminationHandler (TSchedulerTaskHandler *pHandler);

    /// \brief すべての新規タスクをサスペンド状態で作成するようにする
    /// \note SuspendNewTasks()とResumeNewTasks()のネストした呼び出しが可能である
    void SuspendNewTasks (void);
    /// \brief サスペンド状態の新規タスクの作成を停止し、\n
    ///       サスペンド状態で作成されたタスクを開始する
    void ResumeNewTasks (void);

    /// \brief タスクリストを作成する
    /// \param pTarget 出力に使用するデバイス
    void ListTasks (CDevice *pTarget);

    /// \return システムに唯一つのスケジューラオブジェクトへのポインタ
    static CScheduler *Get (void);

    /// \return このシステムではスケジューラが利用可能か?
    /// \note Circleではスケジューラの使用はオプションである
    static boolean IsActive (void)
    {
        return s_pThis != 0 ? TRUE : FALSE;
    }

private:
    void AddTask (CTask *pTask);
    friend class CTask;

    boolean BlockTask (CTask **ppWaitListHead, unsigned nMicroSeconds);
    void WakeTasks (CTask **ppWaitListHead); // 割り込みコンテキストからの呼び出しが可能
    friend class CSynchronizationEvent;

    void RemoveTask (CTask *pTask);
    unsigned GetNextTask (void); // m_pTaskへのインデックス、タスクが見つからなかった場合はMAX_TASKSを返す

private:
    CTask *m_pTask[MAX_TASKS];      ///< タスク配列
    unsigned m_nTasks;              ///< タスクの数

    CTask *m_pCurrent;              ///< 現在実行中のタスク
    unsigned m_nCurrent;            ///< m_pTaskのインデックス

    TSchedulerTaskHandler *m_pTaskSwitchHandler;        ///< タスクスイッチの際に呼び出されるコールバック関数
    TSchedulerTaskHandler *m_pTaskTerminationHandler;   ///< タスクが終了する際に呼び出されるコールバック関数

    int m_iSuspendNewTasks;         ///< 新規タスクをサスペンド状態で作成するか

    CSpinLock m_SpinLock;           ///< ロック（処理待ちリストを保護）

    static CScheduler *s_pThis;     ///< スケジューラ（システムに一つ）
};

#endif
