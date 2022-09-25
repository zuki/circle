//
// koptions.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2022  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_koptions_h
#define _circle_koptions_h

#include <circle/bcmpropertytags.h>
#include <circle/cputhrottle.h>
#include <circle/types.h>

/**
 * @class CKernelOptions
 * @brief カーネルオプション
 */
class CKernelOptions
{
public:
    /// @brief コンストラクタ
    CKernelOptions (void);
    /// @brief デストラクタ
    ~CKernelOptions (void);

    //! Getter: 画面幅
    unsigned GetWidth (void) const;
    //! Getter: 画面高さ
    unsigned GetHeight (void) const;
    //! Getter: ログデバイス
    const char *GetLogDevice (void) const;
    //! Getter: ログ出力レベル
    unsigned GetLogLevel (void) const;
    //! Getter: キーマップ
    const char *GetKeyMap (void) const;
    //! Getter: USB電源遅延時間
    unsigned GetUSBPowerDelay (void) const;
    //! Getter: USBフルスピードか
    boolean GetUSBFullSpeed (void) const;
    //! Getter: USBブースト
    boolean GetUSBBoost (void) const;
    //! Getter: 無視するUSBインタフェース
    const char *GetUSBIgnore (void) const;          // defaults to empty string
    //! Getter: サウンドデバイス
    const char *GetSoundDevice (void) const;        // defaults to empty string
    //! Getter: サウンドオプション
    unsigned GetSoundOption (void) const;
    //! Getter: CPUスピード
    TCPUSpeed GetCPUSpeed (void) const;
    //! Getter: Soc最大温度
    unsigned GetSoCMaxTemp (void) const;
    //! Getter: GPIOファンピン
    unsigned GetGPIOFanPin (void) const;            // returns 0, if not defined
    //! Getter: タッチスクリーン
    const unsigned *GetTouchScreen (void) const;    // returns 4 values (nullptr if unset)
    //! Getter: オブジェクト自身
    static CKernelOptions *Get (void);

private:
    /// @brief 次の"option=value"ペアを返す
    /// @return 次の"option=value"ペア、ない場合は0
    char *GetToken (void);
    /// @brief "option=value"ペアの値を返す
    /// @param pOption "option=value"ペア
    /// @return '\0'終端のオプション値
    static char *GetOptionValue (char *pOption);
    /// @brief 10進数文字列を数値に変換する
    /// @param pString 文字列
    /// @return 10進数値、エラーの場合は -1
    static unsigned GetDecimal (char *pString);

    // fetches nCount comma-separated decimals from pString to pResult

    /// @brief カンマ区切りの数値文字列から最大nCountの数値を取り出す
    /// @param pString 数値文字列
    /// @param pResult 変換後の数値
    /// @param nCount 最大変換数
    /// @return nCount個あったらTRUE, まだ変換されていない数値があったらFALSE
    static boolean GetDecimals (char *pString, unsigned *pResult, unsigned nCount);

private:
    /// @brief コマンドライン取得のためのMailBox属性
    TPropertyTagCommandLine m_TagCommandLine;
    /// @brief コマンドラインオプション文字列
    char *m_pOptions;
    /// @brief 画面幅
    unsigned m_nWidth;
    /// @brief 画面高さ
    unsigned m_nHeight;
    /// @brief ログデバイス
    char m_LogDevice[20];
    /// @brief ログレベル
    unsigned m_nLogLevel;
    /// @brief キーマップ
    char m_KeyMap[3];
    /// @brief USB電源遅延
    unsigned m_nUSBPowerDelay;
    /// @brief USBフルスピードか
    boolean m_bUSBFullSpeed;
    /// @brief USBブースト
    boolean m_bUSBBoost;
    /// @brief 無視するUSBインタフェース
    char m_USBIgnore[20];
    /// @brief サウンドデバイス
    char m_SoundDevice[20];
    /// @brief サウンドオプション
    unsigned m_nSoundOption;
    /// @brief CPUスピード
    TCPUSpeed m_CPUSpeed;
    /// @brief SoC最大温度
    unsigned m_nSoCMaxTemp;
    /// @brief GPIOファンピン
    unsigned m_nGPIOFanPin;
    /// @brief タッチスクリーンあり
    boolean m_bTouchScreenValid;
    /// @brief タッチスクリーン
    unsigned m_TouchScreen[4];
    /// @brief このオブジェクト
    static CKernelOptions *s_pThis;
};

#endif
