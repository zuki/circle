/** @addtogroup net_core
 *  @{
 */
//
// linklayer.h
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
#ifndef _circle_net_linklayer_h
#define _circle_net_linklayer_h

#include <circle/net/netconfig.h>
#include <circle/net/netdevlayer.h>
#include <circle/net/arphandler.h>
#include <circle/net/ipaddress.h>
#include <circle/macaddress.h>
#include <circle/net/netqueue.h>
#include <circle/macros.h>
#include <circle/types.h>

/// @brief Ethernetヘッダを表す構造体
struct TEthernetHeader
{
    /// @brief 受信者のMACアドレス
    u8  MACReceiver[MAC_ADDRESS_SIZE];
    /// @brief 送信者のMACアドレス
    u8  MACSender[MAC_ADDRESS_SIZE];
    /// @brief プロトコルタイプ
    u16 nProtocolType;
#define ETH_PROT_IP     0x800
#define ETH_PROT_ARP    0x806
}
PACKED;

class CNetworkLayer;

/// @brief データリンク層を表すクラス
class CLinkLayer
{
public:
    /// @brief コンストラクタ
    /// @param pNetConfig ネットワーク構成オブジェクトへのポインタ
    /// @param pNetDevLayer ネットワークデバイス層オブジェクトへのポインタ
    CLinkLayer (CNetConfig *pNetConfig, CNetDeviceLayer *pNetDevLayer);
    /// @brief デストラクタ
    ~CLinkLayer (void);
    /// @brief 初期化関数(ARPハンドラの設定)
    /// @return 常にTRUE
    boolean Initialize (void);

    /// @brief ネットワーク層をアタッチする. \n
    /// 通知のためにネットワーク層へのバックウェイが必要
    /// @param pNetworkLayer ネットワーク層オブジェクトへのポインタ
    void AttachLayer (CNetworkLayer *pNetworkLayer);
    /// @brief データを受信し、適切な受信キューに入れる
    void Process (void);
    /// @brief データを送信する
    /// @param rReceiver 宛先IPアドレス
    /// @param pIPPacket データ
    /// @param nLength データ長
    /// @return 送信の成否
    boolean Send (const CIPAddress &rReceiver, const void *pIPPacket, unsigned nLength);

    /// @brief IPデータを受信する
    /// @param pBuffer データを入れるバッファ（FRAME_BUFFER_SIZEのサイズが必要）
    /// @param pResultLength 受信データ長
    /// @return 受信データが有ればTRUE
    boolean Receive (void *pBuffer, unsigned *pResultLength);

public:
    /// @brief フレームをそのまま送信
    /// @param pFrame フレーム
    /// @param nLength フレーム長
    /// @return 常にTRUEを返す
    boolean SendRaw (const void *pFrame, unsigned nLength);

    /// @brief Raw受信キューのデータを取得する
    /// @param pBuffer 受信バッファ（FRAME_BUFFER_SIZEのサイズが必要）
    /// @param pResultLength 受信したデータ長
    /// @param pSender 送信元MACアドレス（不要なら0）
    /// @return
    boolean ReceiveRaw (void *pBuffer, unsigned *pResultLength, CMACAddress *pSender = 0);

    // nProtocolType is in host byte order

    /// @brief Raw受信タイプをnProtocolTypeにする
    /// @param nProtocolType プロトコルタイプ（ホストのバイトオーダ: LE）
    /// @return すでにRaw受信タイプが設定されていた場合はFALSE
    boolean EnableReceiveRaw (u16 nProtocolType);

private:
    /// @brief 送信が失敗したことをネットワーク層に通知する
    /// @param pReturnedFrame 返されたIPパケット
    /// @param nLength データ長
    void ResolveFailed (const void *pReturnedFrame, unsigned nLength);
    friend class CARPHandler;

private:
    /// @brief ネットワーク構成パラメタオブジェクト
    CNetConfig      *m_pNetConfig;
    /// @brief ネットワークデバイス層オブジェクト
    CNetDeviceLayer *m_pNetDevLayer;
    /// @brief ネットワーク層オブジェクト
    CNetworkLayer   *m_pNetworkLayer;
    /// @brief APRハンドラ
    CARPHandler     *m_pARPHandler;
    /// @brief ARP受信キュー
    CNetQueue       m_ARPRxQueue;
    /// @brief IP受信キュー
    CNetQueue       m_IPRxQueue;
    /// @brief Raw受信キュー
    CNetQueue       m_RawRxQueue;
    /// @brief Rawプロトコルタイプ
    u16             m_nRawProtocolType;
};

/** @} */

#endif
