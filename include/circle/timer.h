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

    /// \brief システム起動後のティック数を取得する
    /// \return システム起動後の1/HZ秒。ラップする可能性がある
    unsigned GetTicks (void) const;

    /// \brief システム起動後の秒数（継続時間）を取得する
    /// \return システム起動後の秒数（継続時間）
    unsigned GetUptime (void) const;

    /// \brief システム時間（秒数）を取得する
    /// \return （timeが設定されている場合は）1970-01-01 00:00:00以来の秒数\n
    /// すわわち、指定のタイムゾーンによる現在時\n
    /// そうでなければ、システム起動後の秒数
    unsigned GetTime (void) const;

    /// \brief GetTime()と同じ関数
    unsigned GetLocalTime (void) const    { return GetTime (); }

    /// \brief マイクロ秒パートのある現在時（GetTime()を参照）を取得する
    /// \param pSeconds 秒数が格納される
    /// \param pMicroSeconds マイクロ秒が格納される
    /// \return timeがvalidであればTRUE
    boolean GetLocalTime (unsigned *pSeconds, unsigned *pMicroSeconds);

    /// \return 1970-01-01 00:00:00以来の現在時（UTC）を取得する\n
    /// timeが未設定でtime zone diff > 0の場合は0
    unsigned GetUniversalTime (void) const;

    /// \brief マイクロ秒パートのある現在時(UTC)を取得する
    /// \param pSeconds 秒数が格納される
    /// \param pMicroSeconds マイクロ秒が格納される
    /// \return timeがvalidであればTRUE\n
    /// timeが未設定でtime zone diff > 0の場合はFALSE
    boolean GetUniversalTime (unsigned *pSeconds, unsigned *pMicroSeconds);

    /// \return "[MMM dD ]HH:MM:SS.ss"、初期されていない場合は0\n
    /// 取得したCStringオブジェクトは呼び出し側で削除する必要がある\n
    /// 指定のタイムゾーンによる現在時
    CString *GetTimeString (void);

    /// \brief 指定した時間後にタイマーが発火し、指定のハンドラを呼び出す\n
    /// カーネルタイマーをスタートさせる
    /// \param nDelay    現在からnDelay/HZ秒後にタイマーは発火
    /// \param pHandler   タイマーが発火された際に呼び出されるハンドラー
    /// \param pParam    最初にハンドラに渡されるユーザ定義パラメタ
    /// \param pContext    ２番めにハンドラに渡されるユーザ定義パラメタ
    /// \return タイマーハンドル（0以外）
    TKernelTimerHandle StartKernelTimer (unsigned nDelay,
                         TKernelTimerHandler *pHandler,
                         void *pParam   = 0,
                         void *pContext = 0);

    /// \brief 実行中のカーネルタイマーをキャンセルする\n
    /// タイマーは発火しない
    /// \param hTimer    タイマーハンドル
    void CancelKernelTimer (TKernelTimerHandle hTimer);

    /// CTimerオブジェクトが利用可能な場合はSimpleMsDelay()よりこちらを使用する\n
    /// \param nMilliSeconds ミリ秒単位の遅延時間 (<= 2000)
    void MsDelay (unsigned nMilliSeconds)    { SimpleMsDelay (nMilliSeconds); }

    /// CTimerオブジェクトが利用可能な場合はSimpleusDelay()よりこちらを使用する\n
    /// \param nMicroSeconds マイクロ秒単位の遅延時間
    void usDelay (unsigned nMicroSeconds)    { SimpleusDelay (nMicroSeconds); }

#ifdef CALIBRATE_DELAY
    /// \param nNanoSeconds ナノ秒単位の遅延時間
    void nsDelay (unsigned nNanoSeconds)    { DelayLoop (m_nusDelay * nNanoSeconds / 1000); }
#endif

    /// \return システムに唯一存在するCTimerオブジェクトへのパインた
    static CTimer *Get (void);

    /// CTimerを構築以前に使用可能
    /// \param nMilliSeconds ミリ秒単位の遅延時間
    static void SimpleMsDelay (unsigned nMilliSeconds);

    /// CTimerを構築以前に使用可能
    /// \param nMicroSeconds マイクロ秒単位の遅延時間
    static void SimpleusDelay (unsigned nMicroSeconds);

    /// \param pHandler SetTime()実行時に呼び出され、時刻を確認するハンドラ
    void RegisterUpdateTimeHandler (TUpdateTimeHandler *pHandler);

    /// \param pHandler タイマーティック毎（毎秒HZ回）に呼び出されるハンドラ
    void RegisterPeriodicHandler (TPeriodicTimerHandler *pHandler);

private:
    /// @brief 登録済みのカーネルタイマーを発火させる
    void PollKernelTimers (void);

    /// @brief 物理カウンタ割り込みの実際の割り込みハンドラ
    void InterruptHandler (void);

    /// @brief 物理カウンタ割り込みで登録される割り込みハンドラスタブ
    /// @param pParam
    static void InterruptHandler (void *pParam);

    /// @brief 遅延時間を補正する
    void TuneMsDelay (void);

public:
    static int IsLeapYear (unsigned nYear);
    static unsigned GetDaysOfMonth (unsigned nMonth, unsigned nYear);

private:
    CInterruptSystem    *m_pInterruptSystem;    ///< 割り込みシステムへのポインタ

#if defined (USE_PHYSICAL_COUNTER) && AARCH == 64
    u32             m_nClockTicksPerHZTick;     ///< CNTFRQ_EL0 / HZ
#endif

    volatile unsigned     m_nTicks;     ///< jiffies相当 (HZ tick)
    volatile unsigned     m_nUptime;    ///< 稼働時間（秒単位）
    volatile unsigned     m_nTime;      ///< ローカル現在時（秒単位）

    CSpinLock       m_TimeSpinLock;     ///< 上の3つの時間を保護

    int             m_nMinutesDiff;     ///< UTCとの差異（分単位）

    CPtrList        m_KernelTimerList;  ///< カーネルタイマーリスト
    CSpinLock       m_KernelTimerSpinLock;  ///< カーネルタイマーリストを保護

    unsigned        m_nMsDelay;         ///< 時計補正データ（ミリ秒）
    unsigned        m_nusDelay;         ///< 時計補正データ（マイクロ秒）

    TUpdateTimeHandler    *m_pUpdateTimeHandler;    ///< nTime更新ハンドラへのポインタ

#define TIMER_MAX_PERIODIC_HANDLERS    4
    TPeriodicTimerHandler    *m_pPeriodicHandler[TIMER_MAX_PERIODIC_HANDLERS];  ///< 周期実行ハンドラ へのポインタ
    volatile unsigned     m_nPeriodicHandlers;      ///< 周期実行ハンドラindex

    static CTimer *s_pThis;     ///< Singleton Timerオブジェクトへのポインタ

    static const unsigned s_nDaysOfMonth[12];
    static const char *s_pMonthName[12];
};

#endif
