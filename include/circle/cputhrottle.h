//
// cputhrottle.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2016-2022  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_cputhrottle_h
#define _circle_cputhrottle_h

#include <circle/gpiopin.h>
#include <circle/macros.h>
#include <circle/types.h>

enum TCPUSpeed
{
    CPUSpeedLow,
    CPUSpeedMaximum,
    CPUSpeedUnknown
};

enum TSystemThrottledState
{
    SystemStateNothingOccurred        = 0,

    SystemStateUnderVoltageOccurred        = BIT (16),
    SystemStateFrequencyCappingOccurred    = BIT (17),
    SystemStateThrottlingOccurred        = BIT (18),
    SystemStateSoftTempLimitOccurred    = BIT (19)
};

typedef void TSystemThrottledHandler (TSystemThrottledState CurrentState, void *pParam);

/// \warning このクラスを使用する場合はSetOnTemperature()とUpdate()を\n
///     繰り返し呼び出す必要がある。詳細は SetOnTemperature() の説明を\n
///     参照されたい。これを管理する方法がよくわからない場合はこのクラスを\n
///     使用しないこと。

/// \warning CCPUThrottleクラスはI2C転送とSPI転送を行うコードには使用\n
///     できない。CPUクロックのクロックレートの変化は、COREクロックにも影響を\n
///     与える可能性があるため、転送速度を変更してしまう可能性があるからである。

/// \note cmdline.txtのオプション "gpiofanpin=" を使用すると、このクラスは\n
///     CPUクロックではなくGPIOのファンを制御する。

class CCPUThrottle    /// アプリケーションやユーザーの要求、SoCの温度に応じてCPUクロックレートを管理する
{
public:
    /// \param InitialSpeed 初期セットしてセットするCPU速度\n
    /// CPUSpeedUnknown: cmdline.txtのパラメタ"fast=true"を見る。\n
    /// （セットされていない場合は）CPUSpeedLow\n
    /// その他の場合: 選択した値
    CCPUThrottle (TCPUSpeed InitialSpeed = CPUSpeedUnknown);
    ~CCPUThrottle (void);

    /// \return CPUクロックレート変更機能をサポートしているか?\n
    /// その他のメソッドはどのような場合でも呼び出すことができるが、\n
    /// nopの可能性がある。そうでなければ、IsDynamic()がFALSEを\n
    /// 返した場合は不正値を返す
    boolean IsDynamic (void) const;

    /// \return 現在のCPUクロックレートをHz単位で返す。失敗の場合は0を返す。
    unsigned GetClockRate (void) const;
    /// \return 最小CPUクロックレートをHz単位で返す
    unsigned GetMinClockRate (void) const;
    /// \return 最大CPUクロックレートをHz単位で返す
    unsigned GetMaxClockRate (void) const;

    /// \return 現在のSoC温度を℃で返す。失敗の場合は0を返す。
    unsigned GetTemperature (void) const;
    /// \return 最大SoC温度を℃で返す
    unsigned GetMaxTemperature (void) const;

    /// \brief CPU速度をセットする
    /// \param Speed セットする速度（初期値を上書きする）
    /// \param bWait 新しいクロックレートが落ち着くまで待つか？
    /// \return 以前の設定。エラーの場合はCPUSpeedUnknown
    TCPUSpeed SetSpeed (TCPUSpeed Speed, boolean bWait = TRUE);

    /// \brief 現在のSoC温度に応じてCPU速度を設定する。\n
    /// 2〜5秒おきに繰り返し呼び出すことで温度を下げないようにする。\n
    /// SoC温度が60℃（またはcmdline.txtのパラメータ "socmaxtemp "で\n
    /// 設定した値）になるとCPUをスローダウンさせる。
    /// \return 操作の成否
    boolean SetOnTemperature (void);

    /// \brief SetOnTemperature()と同じ関数だが、呼び出し間隔をチェック\n
    /// することなく、何度でも呼び出すことができる。さらに、システム\n
    /// スロットルハンドラが登録されている場合はシステムスロットル状態を\n
    /// チェックする。
    /// \return 操作の成否
    boolean Update (void);

    /// \brief StateMaskで指定されたシステムスロットル状態が発生した際に\n
    /// Update()から呼び出されるコールバック関数を登録する。
    /// \param StateMask 監視するTSystemThrottledState値
    /// \param pHandler 呼び出されるコールバック関数
    /// \param pParam コールバック関数に渡されるユーザパラメタ
    void RegisterSystemThrottledHandler (unsigned StateMask,
                         TSystemThrottledHandler *pHandler, void *pParam = 0);

    /// \brief 現在のCPU状態に関する情報をダンプする
    /// \param bAll すべての情報をダンプする（FALSEの場合は現在のクロックレートと温度のみ）
    void DumpStatus (boolean bAll = TRUE);

    /// \return システムに唯一存在するCCPUThrottleオブジェクトへのポインタ
    static CCPUThrottle *Get (void);

private:
    boolean SetSpeedInternal (TCPUSpeed Speed, boolean bWait);

    boolean CheckThrottledState (void);

    void SetToSetDelay (void);

    static unsigned GetClockRate (unsigned nTagId);     // returns 0 on failure
    static unsigned GetTemperature (unsigned nTagId);   // returns 0 on failure
    static boolean SetClockRate (unsigned nRate, boolean bSkipTurbo);

private:
    boolean  m_bDynamic;
    unsigned m_nMinClockRate;
    unsigned m_nMaxClockRate;
    unsigned m_nMaxTemperature;
    unsigned m_nEnforcedTemperature;

    TCPUSpeed m_SpeedSet;
    unsigned  m_nTicksLastSet;
    unsigned  m_nTicksLastUpdate;

    TSystemThrottledState m_ThrottledStateMask;
    TSystemThrottledState m_LastThrottledState;
    TSystemThrottledHandler *m_pThrottledHandler;
    void *m_pThrottledParam;

    boolean m_bFanConnected;
    CGPIOPin m_FanPin;

    static CCPUThrottle *s_pThis;
};

#endif
