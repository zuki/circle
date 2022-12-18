/** @addtogroup net_core
 *  @{
 */
//
// networklayer.h
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
#ifndef _circle_net_networklayer_h
#define _circle_net_networklayer_h

#include <circle/net/netconfig.h>
#include <circle/net/linklayer.h>
#include <circle/net/netqueue.h>
#include <circle/net/ipaddress.h>
#include <circle/net/icmphandler.h>
#include <circle/net/routecache.h>
#include <circle/macros.h>
#include <circle/types.h>

/// @brief IPヘッダを表す構造体
struct TIPHeader
{
    /// @brief IPのバージョンとヘッダ長（4bit + 4bit）
    u8    nVersionIHL;
#define IP_VERSION                  4
#define IP_HEADER_LENGTH_DWORD_MIN  5
#define IP_HEADER_LENGTH_DWORD_MAX  6
    /// @brief サービスタイプ
    u8    nTypeOfService;
#define IP_TOS_ROUTINE              0
    /// @brief パケット総サイズ（ヘッダ＋データ）
    u16    nTotalLength;
    /// @brief 識別番号
    u16    nIdentification;
#define IP_IDENTIFICATION_DEFAULT   0
    /// @brief フラグとフラグメントオフセット(3bit + 13bit)
    u16    nFlagsFragmentOffset;
#define IP_FRAGMENT_OFFSET(field)   ((field) & 0x1F00)
    #define IP_FRAGMENT_OFFSET_FIRST    0
#define IP_FLAGS_DF                 (1 << 6)    // valid without BE()
#define IP_FLAGS_MF                 (1 << 5)
    /// @brief 生存期間（TTL）
    u8    nTTL;
#define IP_TTL_DEFAULT              64
    /// @brief プロトコル
    u8    nProtocol;                // see: in.h
    /// @brief ヘッダチェックサム
    u16    nHeaderChecksum;
    /// @brief 送信元IPアドレス
    u8    SourceAddress[IP_ADDRESS_SIZE];
    /// @brief 宛先IPアドレス
    u8    DestinationAddress[IP_ADDRESS_SIZE];
    //u32    nOptionsPadding;            // オプション
#define IP_OPTION_SIZE              0    // 当面使用しない
}
PACKED;

/// @brief プライベートデータ
struct TNetworkPrivateData
{
    /// @brief プロトコル
    u8    nProtocol;
    /// @brief 送信元IPアドレス
    u8    SourceAddress[IP_ADDRESS_SIZE];
    /// @brief 宛先IPアドレス
    u8    DestinationAddress[IP_ADDRESS_SIZE];
};

/// @brief ネットワーク層を表すクラス
class CNetworkLayer
{
public:
    /// @brief コンストラクタ
    /// @param pNetConfig ネットワーク構成パラメタオブジェクトへのポインタ
    /// @param pLinkLayer データリンク層オブジェクトへのポインタ
    CNetworkLayer (CNetConfig *pNetConfig, CLinkLayer *pLinkLayer);
    /// @brief デストラクタ
    ~CNetworkLayer (void);
    /// @brief 初期化関数
    /// @return 常にTRUEを返す
    boolean Initialize (void);
    /// @brief 処理関数
    void Process (void);
    /// @brief パケットを送信する
    /// @param rReceiver 宛先IPアドレス
    /// @param pPacket 送信データ
    /// @param nLength データ長
    /// @param nProtocol プロトコル
    /// @return 送信の成否
    boolean Send (const CIPAddress &rReceiver, const void *pPacket, unsigned nLength, int nProtocol);

    /// @brief パケットを受信する\n
    /// pBufferはFRAME_BUFFER_SIZEのサイズがなければならない
    /// @param pBuffer 受信バッファ
    /// @param pResultLength 実際に受信したサイズを受け取る変数へのポインタ
    /// @param pSender 送信者のIPアドレス
    /// @param pReceiver 受信者のIPアドレス
    /// @param pProtocol プロトコルを受け取る変数へのポインタ
    /// @return 受信の成否
    boolean Receive (void *pBuffer, unsigned *pResultLength,
             CIPAddress *pSender, CIPAddress *pReceiver, int *pProtocol);
    /// @brief 通知を受信する
    /// @param pType 通知の種類を受け取る変数へのポインタ
    /// @param pSender 送信者を受け取る変数へのポインタ
    /// @param pReceiver 受信者受け取る変数へのポインタ
    /// @param pSendPort 送信ポート受け取る変数へのポインタ
    /// @param pReceivePort 受信ポート受け取る変数へのポインタ
    /// @param pProtocol プロトコル受け取る変数へのポインタ
    /// @return 受信の成否
    boolean ReceiveNotification (TICMPNotificationType *pType,
                     CIPAddress *pSender, CIPAddress *pReceiver,
                     u16 *pSendPort, u16 *pReceivePort,
                     int *pProtocol);

private:
    /// @brief ルートキャッシュに宛先IPとそのゲートウェイアドレスを追加する
    /// @param pDestIP 宛先IP
    /// @param pGatewayIP ゲートウェイアドレス
    void AddRoute (const u8 *pDestIP, const u8 *pGatewayIP);
    /// @brief 指定した宛先IPアドレスへのゲートウェイアドレスを取得する
    /// @param pDestIP 宛先IPアドレス
    /// @return ゲートウェイアドレス
    const u8 *GetGateway (const u8 *pDestIP) const;
    friend class CICMPHandler;

    /// @brief 通知のためにIPパケットをCIMPハンドラに送信する
    /// @param nICMPCode エラーコード
    /// @param pReturnedPacket 返されたパケット
    /// @param nLength データ長
    void SendFailed (unsigned nICMPCode, const void *pReturnedPacket, unsigned nLength);
    friend class CLinkLayer;

private:
    /// @brief ネットワーク構成パラメタ
    CNetConfig   *m_pNetConfig;
    /// @brief データリンク層オブジェクト
    CLinkLayer   *m_pLinkLayer;
    /// @brief ICMPハンドラ
    CICMPHandler *m_pICMPHandler;
    /// @brief 受信キュー
    CNetQueue m_RxQueue;
    /// @brief ICMP受信キュー
    CNetQueue m_ICMPRxQueue;
    /// @brief ICMP通知キュー
    CNetQueue m_ICMPNotificationQueue;

    CRouteCache m_RouteCache;
};

/** @} */
#endif
