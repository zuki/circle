/** @defgroup net NET関連
 *
 *  @defgroup net_core NETコアクラス
 *  @ingroup net
 *  @{
*/
//
// netsubsystem.h
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


#ifndef _circle_net_netsubsystem_h
#define _circle_net_netsubsystem_h

#include <circle/net/netconfig.h>
#include <circle/net/netdevlayer.h>
#include <circle/net/linklayer.h>
#include <circle/net/networklayer.h>
#include <circle/net/transportlayer.h>
#include <circle/string.h>
#include <circle/types.h>

#define DEFAULT_HOSTNAME    "raspberrypi"

class CDHCPClient;

/// @brief ネットワークサブシステムクラス
class CNetSubSystem
{
public:
    /// @brief コンストラクタ
    /// @param pIPAddress IPアドレス（pIPAddress == 0の場合はDHCPを使用）
    /// @param pNetMask サブネットマスク
    /// @param pDefaultGateway デフォルトゲートウェイ
    /// @param pDNSServer DNSサーバ
    /// @param pHostname ホスト名（ホスト名がない場合は0）
    /// @param DeviceType デバイスタイプ（デフォルトはEthernet）
    CNetSubSystem (
            const u8    *pIPAddress         = 0,
            const u8    *pNetMask           = 0,
            const u8    *pDefaultGateway    = 0,
            const u8    *pDNSServer         = 0,
            const char  *pHostname          = DEFAULT_HOSTNAME,
            TNetDeviceType DeviceType       = NetDeviceTypeEthernet);
    /// @brief デストラクタ
    ~CNetSubSystem (void);
    /// @brief 初期化関数
    /// @param bWaitForActivate ネットワークのが立ち上がるまで待つか
    /// @return 処理の成否
    boolean Initialize (boolean bWaitForActivate = TRUE);
    /// @brief 処理を行う
    void Process (void);

    // getter

    /// @brief ネットワーク構成オブジェクトを取得
    /// @return ネットワーク構成オブジェクトへのポインタ
    CNetConfig *GetConfig (void);
    /// @brief 物理層のオブジェクトを取得
    /// @return 物理層のオブジェクトへのポインタ
    CNetDeviceLayer *GetNetDeviceLayer (void);
    /// @brief リンク層のオブジェクトを取得
    /// @return ・リンク層のオブジェクトへのポインタ
    CLinkLayer *GetLinkLayer (void);
    /// @brief トランスポート層のオブジェクトを取得
    /// @return トランスポート層のオブジェクトへのポインタ
    CTransportLayer *GetTransportLayer (void);
    /// @brief DHCPを使うのであればDHCPはバインドされているか
    /// @return バインドの有無
    boolean IsRunning (void) const;
    /// @brief 自オブジェクトを取得する
    /// @return 自オブジェクトへのポインタ
    static CNetSubSystem *Get (void);

private:
    /// @brief ホスト名
    CString         m_Hostname;
    /// @brief ネットワーク構成のオブジェクト
    CNetConfig      m_Config;
    /// @brief 物理層のオブジェクト
    CNetDeviceLayer m_NetDevLayer;
    /// @brief リンク層のオブジェクト
    CLinkLayer      m_LinkLayer;
    /// @brief ネットワーク層のオブジェクト
    CNetworkLayer   m_NetworkLayer;
    /// @brief トランスポート層のオブジェクト
    CTransportLayer m_TransportLayer;
    /// @brief DSCPを使うか
    boolean         m_bUseDHCP;
    /// @brief DHCPクライアントオブジェクト
    CDHCPClient    *m_pDHCPClient;
    /// @brief 自オブジェクトへのポインタ
    static CNetSubSystem *s_pThis;
};

/** @} */

#endif
