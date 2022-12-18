/** @addtogroup net_core
 *  @{
 */
//
// netconnection.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2018  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_net_netconnection_h
#define _circle_net_netconnection_h

#include <circle/net/netconfig.h>
#include <circle/net/networklayer.h>
#include <circle/net/ipaddress.h>
#include <circle/net/icmphandler.h>
#include <circle/net/checksumcalculator.h>
#include <circle/types.h>

/// @brief ネットワーク通信を表すクラス
class CNetConnection
{
public:
    /// @brief コンストラクタ
    /// @param pNetConfig ネットワーク構成パラメタオブジェクトへのポインタ
    /// @param pNetworkLayer ネットワークレイアオブジェクトへのポインタ
    /// @param rForeignIP   通信相手のアドレス
    /// @param nForeignPort 通信相手のポート
    /// @param nOwnPort 自身のポート
    /// @param nProtocol 通信プロトコル
    CNetConnection (CNetConfig    *pNetConfig,
            CNetworkLayer  *pNetworkLayer,
            CIPAddress     &rForeignIP,
            u16             ForeignPort,
            u16             nOwnPort,
            int             nProtocol);
    /// @brief コンストラクタ（相手先を指定しない）
    /// @param pNetConfig ネットワーク構成パラメタオブジェクトへのポインタ
    /// @param pNetworkLayer ネットワークレイアオブジェクトへのポインタ
    /// @param nOwnPort 自身のポート
    /// @param nProtocol 通信プロトコル
    CNetConnection (CNetConfig    *pNetConfig,
            CNetworkLayer  *pNetworkLayer,
            u16             nOwnPort,
            int             nProtocol);
    /// @brief デストラクタ
    virtual ~CNetConnection (void);
    /// @brief 宛先IPアドレスを取得
    /// @return 宛先IPアドレスのバイト列
    const u8 *GetForeignIP (void) const;
    /// @brief 自身のポートを取得
    /// @return ポート
    u16 GetOwnPort (void) const;
    /// @brief プロトコルを取得
    /// @return プロトコル
    int GetProtocol (void) const;

    virtual int Connect (void) = 0;
    virtual int Accept (CIPAddress *pForeignIP, u16 *pForeignPort) = 0;
    virtual int Close (void) = 0;

    virtual int Send (const void *pData, unsigned nLength, int nFlags) = 0;
    virtual int Receive (void *pBuffer, int nFlags) = 0;

    virtual int SendTo (const void *pData, unsigned nLength, int nFlags, CIPAddress    &rForeignIP, u16 nForeignPort) = 0;
    virtual int ReceiveFrom (void *pBuffer, int nFlags, CIPAddress *pForeignIP, u16 *pForeignPort) = 0;

    virtual int SetOptionBroadcast (boolean bAllowed) = 0;

    virtual boolean IsConnected (void) const = 0;
    virtual boolean IsTerminated (void) const = 0;

    virtual void Process (void) = 0;

    // returns: -1: invalid packet, 0: not to me, 1: packet consumed
    virtual int PacketReceived (const void *pPacket, unsigned nLength,
                    CIPAddress &rSenderIP, CIPAddress &rReceiverIP, int nProtocol) = 0;

    // returns: 0: not to me, 1: notification consumed
    virtual int NotificationReceived (TICMPNotificationType Type,
                      CIPAddress &rSenderIP, CIPAddress &rReceiverIP,
                      u16 nSendPort, u16 nReceivePort,
                      int nProtocol) = 0;

protected:
    /// @brief ネットワーク構成オブジェクト
    CNetConfig     *m_pNetConfig;
    /// @brief ネットワーク層オブジェクト
    CNetworkLayer  *m_pNetworkLayer;
    /// @brief 宛先IPアドレス
    CIPAddress      m_ForeignIP;
    /// @brief 宛先ポート
    u16             m_nForeignPort;
    /// @brief 自身のポート
    u16             m_nOwnPort;
    /// @brief プロトコル
    int             m_nProtocol;
    /// @brief チェックサム計算器
    CChecksumCalculator m_Checksum;
};

/** @} */

#endif
