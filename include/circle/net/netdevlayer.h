/** @addtogroup net_core
 *  @{
 */
//
// netdevlayer.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2020  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_net_netdevlayer_h
#define _circle_net_netdevlayer_h

#include <circle/net/netconfig.h>
#include <circle/netdevice.h>
#include <circle/net/netqueue.h>
#include <circle/bcm54213.h>
#include <circle/types.h>

/// @brief 物理層（ネットワークデバイス）を表すクラス
class CNetDeviceLayer
{
public:
    /// @brief コンストラクタ
    /// @param pNetConfig ネットワーク構成オブジェクトへのポインタ
    /// @param DeviceType ネットワークデバイスタイプ
    CNetDeviceLayer (CNetConfig *pNetConfig, TNetDeviceType DeviceType);

    /// @brief デストラクタ
    ~CNetDeviceLayer (void);

    /// @brief 初期化関数（bWaitForActivate=FALSEの場合は直ちにTRUEで返る）
    /// @param bWaitForActivate デバイスの活性化を待つか
    /// @return 初期化の成否
    boolean Initialize (boolean bWaitForActivate);

    /// @brief 送受信を行う
    void Process (void);

    /// @brief デバイスのMACアドレスを取得する
    /// @return デバイスのMACアドレス、デバイスが設定されていない場合は0
    const CMACAddress *GetMACAddress (void) const;

    /// @brief 送信キューにデータを追加する
    /// @param pBuffer データバッファ
    /// @param nLength データ長
    void Send (const void *pBuffer, unsigned nLength);

    /// @brief 受信キューからデータを取得する
    /// @param pBuffer 受信バッファ
    /// @param pResultLength データ長
    /// @return 操作の成否
    boolean Receive (void *pBuffer, unsigned *pResultLength);

    /// @brief デバイスが利用可能か
    /// @return 可能であればTRUE
    boolean IsRunning (void) const;

private:
    /// @brief デバイスタイプ
    TNetDeviceType m_DeviceType;
    /// @brief ネットワーク構成パラメタ
    CNetConfig *m_pNetConfig;
    /// @brief ネットワークデバイス
    CNetDevice *m_pDevice;
    /// @brief 送信キュー
    CNetQueue m_TxQueue;
    /// @brief 受信キュー
    CNetQueue m_RxQueue;

#if RASPPI >= 4
    CBcm54213Device m_Bcm54213;
#endif
};

/** @} */
#endif
