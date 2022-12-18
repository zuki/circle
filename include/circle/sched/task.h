//
/// task.h
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
#ifndef _circle_sched_task_h
#define _circle_sched_task_h

#include <circle/sched/taskswitch.h>
#include <circle/sched/synchronizationevent.h>
#include <circle/sysconfig.h>
#include <circle/string.h>
#include <circle/types.h>

enum TTaskState
{
    TaskStateNew,
    TaskStateReady,
    TaskStateBlocked,
    TaskStateBlockedWithTimeout,
    TaskStateSleeping,
    TaskStateTerminated,
    TaskStateUnknown
};

class CScheduler;

class CTask    /// このクラスをオーバロードし、Run()を定義し、そのクラスをnewすると起動する
{
public:
    /// \param nStackSize このタスクのスタックサイズ（メインタスクでは内的に0が使用される）
    /// \param bCreateSuspended タスクが初期状態で実行可能でない場合、TRUEに設定する
    CTask (unsigned nStackSize = TASK_STACK_SIZE, boolean bCreateSuspended = FALSE);

    virtual ~CTask (void);

    /// \brief このメソッドをオーバーライドして、クラスのエントリポイントを定義する
    virtual void Run (void);

    /// \brief bCreateSuspended = TRUEで作成されたタスクを起動する。\n
    /// または、Suspend()した後に再起動する
    void Start (void);
    /// \brief Resume()が呼び出されるまでタスクの実行を一時停止する
    void Suspend (void);
    /// \brief 一時停止されたタスクを（再）起動する別メソッド
    void Resume (void)            { Start (); }
    /// \return タスクは実行を一時停止しているか?
    boolean IsSuspended (void) const    { return m_bSuspended; }

    /// \brief このタスクの実行を終了する
    /// \note このタスクからしか呼び出せない
    /// \note Run()からのリターンでもタスクは終了する
    void Terminate (void);
    /// \brief このタスクの終了を待つ
    /// \note 他のタスクからしか呼び出せない
    void WaitForTermination (void);

    /// \brief このタスクに指定の名前をセットする
    /// \param pName このタスクの名前を示す文字列
    void SetName (const char *pName);
    /// \return 0終端の文字列へのポインタ（明示的にセットされていない場合は"@this_address"）
    const char *GetName (void) const;

#define TASK_USER_DATA_KTHREAD          0    // Linuxドライバーのエミュレーション
#define TASK_USER_DATA_ERROR_STACK      1    // Plan 9ドライバーのエミュレーション
#define TASK_USER_DATA_USER             2    // アプリケーションで自由に利用可能
#define TASK_USER_DATA_SLOTS            3    // 利用可能なスロットの数
    /// \brief このタスクのユーザポインタをセットする
    /// \param pData 任意のユーザポインタ
    /// \param nSlot セットするスロット
    /// \note スロット TASK_USER_DATA_USER はアプリケーションで自由に利用可能
    void SetUserData (void *pData, unsigned nSlot);
    /// \brief スロットからユーザポインタを取得する
    /// \param nSlot 読み込むスロット
    /// \return 事前にSetUserData()でセットされた任意のユーザポインタ
    void *GetUserData (unsigned nSlot);

private:
    TTaskState GetState (void) const    { return m_State; }
    void SetState (TTaskState State)    { m_State = State; }

    unsigned GetWakeTicks (void) const    { return m_nWakeTicks; }
    void SetWakeTicks (unsigned nTicks)    { m_nWakeTicks = nTicks; }

    TTaskRegisters *GetRegs (void)        { return &m_Regs; }   // Task Context

    friend class CScheduler;

private:
    void InitializeRegs (void);

    static void TaskEntry (void *pParam);

private:
    volatile TTaskState m_State;        ///< タスクの状態
    boolean             m_bSuspended;   ///< 一時停止中
    unsigned            m_nWakeTicks;   ///< 起床チケット
    TTaskRegisters      m_Regs;         ///< タスクコンテキスト
    unsigned            m_nStackSize;   ///< スタックサイズ
    u8                 *m_pStack;       ///< スタックポインタ
    CString             m_Name;         ///< タスク名
    void               *m_pUserData[TASK_USER_DATA_SLOTS];  ///< ユーザデータ
    CSynchronizationEvent m_Event;      ///< イベント
    CTask              *m_pWaitListNext;  ///< イベント待ちのタスクリストの次のエントリ
};

#endif
