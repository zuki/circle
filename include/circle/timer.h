//
/// \file timer.h
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
#ifndef _circle_timer_h
#define _circle_timer_h

#include <circle/interrupt.h>
#include <circle/string.h>
#include <circle/ptrlist.h>
#include <circle/sysconfig.h>
#include <circle/spinlock.h>
#include <circle/types.h>

#define HZ              100     ///< 1秒あたりのティック数

#define MSEC2HZ(msec)   ((msec) * HZ / 1000)

typedef uintptr TKernelTimerHandle;

typedef void TKernelTimerHandler (TKernelTimerHandle hTimer, void *pParam, void *pContext);

/// \brief 時刻更新ハンドラ
/// \param nNewTime 新たにセットする時刻（1970-01-01 00:00:00 UTC以来の秒数）
/// \param nOldTime 現在の時刻（1970-01-01 00:00:00 UTC以来の秒数）
/// \return 新しい時刻がセットされたらTRUE、時刻が不正だったらFALSE（設定されない）
typedef boolean TUpdateTimeHandler (unsigned nNewTime, unsigned nOldTime);

typedef void TPeriodicTimerHandler (void);

extern "C" void DelayLoop (unsigned nCount);

/// @brief タイマークラス. \n
/// システムクロックを管理し、カーネルタイマーとキャリブレートされた遅延ループをサポートする
class CTimer
{
public:
    /// @brief コンストラクタ
    /// @param pInterruptSystem 割り込みシステムへのポインタ
    CTimer (CInterruptSystem *pInterruptSystem);
    /// @brief デストラクタ
    ~CTimer (void);
    /// @brief 初期化関数
    /// @return 常にTRUE
    boolean Initialize (void);

    /// \brief タイムゾーンを設定する（デフォルトは0, GMT）
    /// \param nMinutesDiff    UTCとの差（分単位）
    /// \return 操作の可否
    boolean SetTimeZone (int nMinutesDiff);
    /// \brief タイムゾーン（UTCとの差）を取得する
    /// \return UTCとの差
    int GetTimeZone (void) const;

    /// \brief 時刻を設定する
    /// \param nTime 1970-01-01 00:00:00以来の秒数
    /// \param bLocal  nTimeはタイムゾーンの値か
    /// \return 操作は成功か? bLocal == FALSEで値が非常に小さい場合に失敗する可能性がある
    boolean SetTime (unsigned nTime, boolean bLocal = TRUE);
    /// \brief クロックティックを取得する
    /// \return 1 MHzカウンタによる現在のクロックティック。ラップする可能性がある
    static unsigned GetClockTicks (void);
#define CLOCKHZ    1000000
    /// \brief システムブート後のティック数を取得する
    /// \return システムブート後の1/HZ秒。ラップする可能性がある
    unsigned GetTicks (void) const;
    /// \brief システムブート後の秒数（継続時間）を取得する
    /// \return システムブート後の秒数（継続時間）
    unsigned GetUptime (void) const;

    /// \return Seconds since system boot\n
    /// or since 1970-01-01 00:00:00 (if time was set)\n
    /// Current time according to our time zone
    unsigned GetTime (void) const;
    /// \brief Same function as GetTime()
    unsigned GetLocalTime (void) const    { return GetTime (); }
    /// \brief Get current local time (see GetTime()) with microseconds part
    /// \param pSeconds Seconds will be stored here
    /// \param pMicroSeconds Microseconds will be stored here
    /// \return TRUE if time is valid
    boolean GetLocalTime (unsigned *pSeconds, unsigned *pMicroSeconds);

    /// \return Current time (UTC) in seconds since 1970-01-01 00:00:00\n
    /// may be 0 if time was not set and time zone diff is > 0
    unsigned GetUniversalTime (void) const;
    /// \brief Get current time (UTC) with microseconds part
    /// \param pSeconds Seconds will be stored here
    /// \param pMicroSeconds Microseconds will be stored here
    /// \return TRUE if time is valid\n
    /// may be FALSE if time was not set and time zone diff is > 0
    boolean GetUniversalTime (unsigned *pSeconds, unsigned *pMicroSeconds);

    /// \return "[MMM dD ]HH:MM:SS.ss" or 0 if Initialize() was not called yet,\n
    /// resulting CString object must be deleted by caller\n
    /// Current time according to our time zone
    CString *GetTimeString (void);

    /// \brief Starts a kernel timer which elapses after a given delay,\n
    /// a timer handler gets called then
    /// \param nDelay    Timer elapses after nDelay/HZ seconds from now
    /// \param pHandler    The handler to be called when the timer elapses
    /// \param pParam    First user defined parameter to hand over to the handler
    /// \param pContext    Second user defined parameter to hand over to the handler
    /// \return Timer handle (cannot be 0)
    TKernelTimerHandle StartKernelTimer (unsigned nDelay,
                         TKernelTimerHandler *pHandler,
                         void *pParam   = 0,
                         void *pContext = 0);
    /// \brief Cancel a running kernel timer,\n
    /// The timer will not elapse any more.
    /// \param hTimer    Timer handle
    void CancelKernelTimer (TKernelTimerHandle hTimer);

    /// When a CTimer object is available better use this instead of SimpleMsDelay()\n
    /// \param nMilliSeconds Delay in milliseconds (<= 2000)
    void MsDelay (unsigned nMilliSeconds)    { SimpleMsDelay (nMilliSeconds); }
    /// When a CTimer object is available better use this instead of SimpleusDelay()\n
    /// \param nMicroSeconds Delay in microseconds
    void usDelay (unsigned nMicroSeconds)    { SimpleusDelay (nMicroSeconds); }
#ifdef CALIBRATE_DELAY
    /// \param nNanoSeconds Delay in nanoseconds
    void nsDelay (unsigned nNanoSeconds)    { DelayLoop (m_nusDelay * nNanoSeconds / 1000); }
#endif

    /// \return Pointer to the only CTimer object in the system
    static CTimer *Get (void);

    /// Can be used before CTimer is constructed
    /// \param nMilliSeconds Delay in milliseconds
    static void SimpleMsDelay (unsigned nMilliSeconds);
    /// Can be used before CTimer is constructed
    /// \param nMicroSeconds Delay in microseconds
    static void SimpleusDelay (unsigned nMicroSeconds);

    /// \param pHandler Handler which is called, when SetTime() is invoked to check the time
    void RegisterUpdateTimeHandler (TUpdateTimeHandler *pHandler);

    /// \param pHandler Handler which is called on each timer tick (HZ times per second)
    void RegisterPeriodicHandler (TPeriodicTimerHandler *pHandler);

private:
    void PollKernelTimers (void);

    void InterruptHandler (void);
    static void InterruptHandler (void *pParam);

    void TuneMsDelay (void);

public:
    static int IsLeapYear (unsigned nYear);
    static unsigned GetDaysOfMonth (unsigned nMonth, unsigned nYear);

private:
    CInterruptSystem    *m_pInterruptSystem;

#if defined (USE_PHYSICAL_COUNTER) && AARCH == 64
    u32             m_nClockTicksPerHZTick;
#endif

    volatile unsigned     m_nTicks;
    volatile unsigned     m_nUptime;
    volatile unsigned     m_nTime;            // local time
    CSpinLock         m_TimeSpinLock;

    int             m_nMinutesDiff;        // diff to UTC

    CPtrList         m_KernelTimerList;
    CSpinLock         m_KernelTimerSpinLock;

    unsigned         m_nMsDelay;
    unsigned         m_nusDelay;

    TUpdateTimeHandler    *m_pUpdateTimeHandler;

#define TIMER_MAX_PERIODIC_HANDLERS    4
    TPeriodicTimerHandler    *m_pPeriodicHandler[TIMER_MAX_PERIODIC_HANDLERS];
    volatile unsigned     m_nPeriodicHandlers;

    static CTimer *s_pThis;

    static const unsigned s_nDaysOfMonth[12];
    static const char *s_pMonthName[12];
};

#endif
