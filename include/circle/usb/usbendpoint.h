/** @addtogroup usb_core
 *  @{
 */
//
// usbendpoint.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2019  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_usb_usbendpoint_h
#define _circle_usb_usbendpoint_h

#include <circle/usb/usb.h>
#include <circle/usb/usbdevice.h>
#include <circle/usb/xhciendpoint.h>
#include <circle/types.h>

/// @brief エンドポイント転送種別
enum TEndpointType
{
    EndpointTypeControl,
    EndpointTypeBulk,
    EndpointTypeInterrupt,
    EndpointTypeIsochronous
};

/// @brief USBエンドポイントクラス
class CUSBEndpoint
{
public:
    /// @brief コンストラクタ（EP0を制御）
    /// @param pDevice デバイスクラスへのポインタ
    CUSBEndpoint (CUSBDevice *pDevice);
    /// @brief コンストラクタ
    /// @param pDevice デバイスクラスへのポインタ
    /// @param pDesc エンドポイントディスクリプタオブジェクトへのポインタ
    CUSBEndpoint (CUSBDevice *pDevice, const TUSBEndpointDescriptor *pDesc);
    /// @brief デストラクタ
    ~CUSBEndpoint (void);
    /// @brief このEPのデバイスオブジェクトを取得
    /// @return デバイスオブジェクトへのポインタ
    CUSBDevice *GetDevice (void) const;
    /// @brief EP番号を取得
    /// @return EP番号
    u8 GetNumber (void) const;
    /// @brief EP転送種別を取得
    /// @return EP転送種別
    TEndpointType GetType (void) const;
    /// @brief 転送の方向を取得
    /// @return 転送の方向
    boolean IsDirectionIn (void) const;
    /// @brief パケットの最大サイズを設定
    /// @param nMaxPacketSize パケットの最大サイズ
    /// @return 常にTRUE
    boolean SetMaxPacketSize (u32 nMaxPacketSize);
    /// @brief パケットの最大サイズを取得
    /// @return パケットの最大サイズ
    u32 GetMaxPacketSize (void) const;

#if RASPPI <= 3
    /// @brief インターバルを取得（インタラプト転送以外はpanic）
    /// @return インターバル値（ミリ秒）
    unsigned GetInterval (void) const;
    /// @brief 次の転送のPIDを取得
    /// @param bStatusStage ステータスステージにあるか
    /// @return 次の転送のPID
    TUSBPID GetNextPID (boolean bStatusStage);
    /// @brief 転送をスキップする
    /// @param nPackets 現パケット
    /// @param bStatusStage ステータスステージにあるか
    void SkipPID (unsigned nPackets, boolean bStatusStage);
#endif
    /// @brief 転送をリセットする
    void ResetPID (void);

#if RASPPI >= 4
    CXHCIEndpoint *GetXHCIEndpoint (void);
#endif

private:
    CUSBDevice     *m_pDevice;              /**< デバイス */
    u8              m_ucNumber;             /**< エンドポイント番号 */
    TEndpointType   m_Type;                 /**< 種別 */
    boolean         m_bDirectionIn;         /**< 転送方向 */
    u32             m_nMaxPacketSize;       /**< 最大パケットサイズ */
#if RASPPI <= 3
    unsigned        m_nInterval;            /**< 間隔（ミリ秒） */
    TUSBPID         m_NextPID;              /**< 次のPID */
#endif

#if RASPPI >= 4
    CXHCIEndpoint  *m_pXHCIEndpoint;
#endif
};

/** @} */
#endif
