/** @addtogroup net_core
 *  @{
 */
//
// netconfig.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2016  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_net_netconfig_h
#define _circle_net_netconfig_h

#include <circle/net/ipaddress.h>
#include <circle/types.h>

/// @brief ネットワーク構成を表すクラス\n
/// パラメタはIPアドレス、サブネットマスク、デフォルトゲートウェイ、DNSサーバ
class CNetConfig
{
public:
    /// @brief コンストラクタ
    CNetConfig (void);
    /// デストラクタ
    ~CNetConfig (void);
    /// @brief パラメタをリセットする
    void Reset (void);
    /// @brief DHCPの利用をセットする
    /// @param bUsed DHCPの利用の有無
    void SetDHCP (boolean bUsed);
    /// @brief IPアドレスをセットする
    /// @param nAddress IPアドレス
    void SetIPAddress (u32 nAddress);
    /// @brief サブネットマスクをセットする
    /// @param nNetMask サブネットマスク
    void SetNetMask (u32 nNetMask);
    /// @brief デフォルトゲートウェイをセットする
    /// @param nAddress デフォルトゲートウェイのアドレス
    void SetDefaultGateway (u32 nAddress);
    /// @brief DNSサーバをセットする
    /// @param nAddress DNSサーバのアドレス
    void SetDNSServer (u32 nAddress);
    /// @brief IPアドレスを文字列でセットする
    /// @param pAddress IPアドレスを表す文字列
    void SetIPAddress (const u8 *pAddress);
    /// @brief サブネットマスクを文字列でセットする
    /// @param pNetMask サブネットマスクを表す文字列
    void SetNetMask (const u8 *pNetMask);
    /// @brief デフォルトゲートウェイを文字列でセットする
    /// @param pAddress デフォルトゲートウェイを表す文字列
    void SetDefaultGateway (const u8 *pAddress);
    /// @brief DNSサーバを文字列でセットする
    /// @param pAddress 文字列を表す文字列
    void SetDNSServer (const u8 *pAddress);
    /// @brief DHCPを使用するか
    /// @return 使用する場合はTRUE，使用しない場合はFALSE
    boolean IsDHCPUsed (void) const;
    /// @brief IPアドレスを取得する
    /// @return IPアドレス
    const CIPAddress *GetIPAddress (void) const;
    /// @brief サブネットマスクを取得する
    /// @return サブネットマスク文字列
    const u8 *GetNetMask (void) const;
    /// @brief デフォルトゲートウェイを取得する
    /// @return デフォルトゲートウェイアドレス
    const CIPAddress *GetDefaultGateway (void) const;
    /// @brief DNSサーバを取得する
    /// @return DNSサーバアドレス
    const CIPAddress *GetDNSServer (void) const;
    /// @brief ブロードキャストアドレスを取得する
    /// @return ブロードキャストアドレス
    const CIPAddress *GetBroadcastAddress (void) const;

private:
    /// @brief ブロードキャストアドレスを更新する
    void UpdateBroadcastAddress (void);

private:
    /// @brief DHCPの使用の有無
    boolean m_bUseDHCP;
    /// @brief IPアドレス
    CIPAddress m_IPAddress;
    /// @brief サブネットマスク
    CIPAddress m_NetMask;
    /// @brief デフォルトゲートウェイ
    CIPAddress m_DefaultGateway;
    /// @brief DNSサーバ
    CIPAddress m_DNSServer;
    /// @brief ブロードキャストアドレス
    CIPAddress m_BroadcastAddress;
};

/** @} */
#endif
