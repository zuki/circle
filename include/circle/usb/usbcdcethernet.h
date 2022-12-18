/** @addtogroup usb_core
 *  @{
 */
//
// usbcdcethernet.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2017-2019  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_usb_usbcdcethernet_h
#define _circle_usb_usbcdcethernet_h

#include <circle/netdevice.h>
#include <circle/usb/usbfunction.h>
#include <circle/usb/usbendpoint.h>
#include <circle/usb/usbrequest.h>
#include <circle/macaddress.h>
#include <circle/types.h>

/// @brief CDC Ethernetデバイスクラス
class CUSBCDCEthernetDevice : public CUSBFunction, CNetDevice
{
public:
    /// @brief コンストラクタ
    /// @param pFunction 属性クラスオブジェクトへのポインタ
    CUSBCDCEthernetDevice (CUSBFunction *pFunction);
    /// @brief デストラクタ
    ~CUSBCDCEthernetDevice (void);
    /// @brief コンフィグレーションを行う
    /// @return 操作の成否
    boolean Configure (void);
    /// @brief MACアドレスを取得
    /// @return  MACアドレスへのポインタ
    const CMACAddress *GetMACAddress (void) const;
    /// @brief フレームの送信
    /// @param pBuffer データバッファへのポインタ
    /// @param nLength データ長
    /// @return 操作の成否
    boolean SendFrame (const void *pBuffer, unsigned nLength);

    /// @brief フレームの受信
    /// @param pBuffer データバッファへのポインタ（FRAME_BUFFER_SIZEのサイズが必要）
    /// @param pResultLength 受信したデータ長
    /// @return 操作の成否
    boolean ReceiveFrame (void *pBuffer, unsigned *pResultLength);

private:
    /// @brief MACアドレスの初期化
    /// @param iMACAddress MACアドレス
    /// @return 操作の成否
    boolean InitMACAddress (u8 iMACAddress);

private:
    /// @brief バルク転送入力用パイプ
    CUSBEndpoint   *m_pEndpointBulkIn;
    /// @brief バルク転送出力用パイプ
    CUSBEndpoint   *m_pEndpointBulkOut;
    /// @brief MACアドレス
    CMACAddress     m_MACAddress;
};

/** @} */

#endif
