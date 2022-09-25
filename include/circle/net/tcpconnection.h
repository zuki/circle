//
// tcpconnection.h
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
#ifndef _circle_net_tcpconnection_h
#define _circle_net_tcpconnection_h

#include <circle/net/netconnection.h>
#include <circle/net/networklayer.h>
#include <circle/net/ipaddress.h>
#include <circle/net/icmphandler.h>
#include <circle/net/netqueue.h>
#include <circle/net/retransmissionqueue.h>
#include <circle/net/retranstimeoutcalc.h>
#include <circle/sched/synchronizationevent.h>
#include <circle/timer.h>
#include <circle/spinlock.h>
#include <circle/types.h>

/// @brief TCP状態
enum TTCPState
{
    TCPStateClosed,
    TCPStateListen,
    TCPStateSynSent,
    TCPStateSynReceived,
    TCPStateEstablished,
    TCPStateFinWait1,
    TCPStateFinWait2,
    TCPStateCloseWait,
    TCPStateClosing,
    TCPStateLastAck,
    TCPStateTimeWait
};

/// @brief TCPタイマー
enum TTCPTimer
{
    TCPTimerUser,
    TCPTimerRetransmission,
    TCPTimerTimeWait,
    TCPTimerUnknown
};

struct TTCPHeader;

/// @brief TCPコネクションを表すクラス
class CTCPConnection : public CNetConnection
{
public:
    /// @brief コンストラクタ（アクティブOPEN）
    /// @param pNetConfig ネットワーク構成オブジェクトへのポインタ
    /// @param pNetworkLayer ネットワーク層オブジェクトへのポインタ
    /// @param rForeignIP 宛先IPアドレス
    /// @param nForeignPort 宛先ポート
    /// @param nOwnPort 自ポート
    CTCPConnection (CNetConfig *pNetConfig,
            CNetworkLayer      *pNetworkLayer,
            CIPAddress         &rForeignIP,
            u16                 nForeignPort,
            u16                 nOwnPort);
    /// @brief コンストラクタ（パッシブOPEN）
    /// @param pNetConfig ネットワーク構成オブジェクトへのポインタ
    /// @param pNetworkLayer ネットワーク層オブジェクトへのポインタ
    /// @param nOwnPort 自ポート
    CTCPConnection (CNetConfig *pNetConfig,
            CNetworkLayer      *pNetworkLayer,
            u16                 nOwnPort);
    /// @brief デストラクタ
    ~CTCPConnection (void);
    /// @brief コネクションを確立する
    /// @return エラーの場合は < 0
    int Connect (void);
    /// @brief acceptする
    /// @param pForeignIP 宛先IPをセットする変数へのポインタ
    /// @param pForeignPort 宛先ポートをセットする変数へのポインタ
    /// @return エラーの場合は < 0
    int Accept (CIPAddress *pForeignIP, u16 *pForeignPort);
    /// @brief コネクションを閉じる
    /// @return 成功したら0、エラーの場合は < 0
    int Close (void);
    /// @brief 送信データを送信キューに入れる
    /// @param pData 送信データ
    /// @param nLength 送信データ長
    /// @param nFlags フラグ（MSG_DONTWAITのみ受け付ける）
    /// @return エラーの場合は < 0
    int Send (const void *pData, unsigned nLength, int nFlags);
    /// @brief 受信キューからデータを受信する. \n
    /// フラグがMSG_DONTWAITの場合はデータがない場合は直ちに変える。\n
    /// そうでなければ受信データが有るまでブロックする
    /// @param pBuffer 受信するバッファ
    /// @param nFlags フラグ（MSG_DONTWAITのみ受け付ける）
    /// @return 受信したデータ長。エラーの場合は < 0
    int Receive (void *pBuffer, int nFlags);
    /// @brief 宛先を指定してデータを送信する. \n
    /// この実装では宛先は無視している
    /// @param pData 送信データ
    /// @param nLength 送信データ長
    /// @param nFlags フラグ（MSG_DONTWAITのみ受け付ける）
    /// @param rForeignIP 宛先IPアドレス
    /// @param nForeignPort 宛先ポート
    /// @return エラーの場合は < 0
    int SendTo (const void *pData, unsigned nLength, int nFlags, CIPAddress    &rForeignIP, u16 nForeignPort);
    /// @brief 受信キューからデータを受信する. \n
    /// データがあり、rForeignIP, nForeignPortが指定された場合は宛先を
    /// 設定する
    /// @param pBuffer 受信バッファ
    /// @param nFlags フラグ（MSG_DONTWAITのみ受け付ける）
    /// @param pForeignIP 宛先IPをセットする変数へのポインタ
    /// @param pForeignPort 宛先ポートをセットする変数へのポインタ
    /// @return 成功の場合は0, エラーの場合は < 0
    int ReceiveFrom (void *pBuffer, int nFlags, CIPAddress *pForeignIP, u16 *pForeignPort);
    /// @brief 未実装
    /// @return 常に0
    int SetOptionBroadcast (boolean bAllowed);
    /// @brief コネクション済みか
    /// @return コネクション済みの場合はTRUE
    boolean IsConnected (void) const;
    /// @brief コネクションはクローズされているか
    /// @return クローズされている場合はTRUE
    boolean IsTerminated (void) const;
    /// @brief 処理をすすめる
    void Process (void);

    // returns: -1: invalid packet, 0: not to me, 1: packet consumed

    /// @brief パケットを受け取る
    /// @param pPacket パケットを受け取るバッファ
    /// @param nLength パケット長
    /// @param rSenderIP 宛先IPアドレスをセットする変数へのポインタ
    /// @param rReceiverIP 受信者IPアドレスをセットする変数へのポインタ
    /// @param nProtocol プロトコル
    /// @return 不正なパケットの場合は-1, 自分宛てでない場合は0, パケットを受信した場合は1
    int PacketReceived (const void *pPacket, unsigned nLength,
                CIPAddress &rSenderIP, CIPAddress &rReceiverIP, int nProtocol);

    // returns: 0: not to me, 1: notification consumed

    /// @brief 通知を受け取る
    /// @param Type 通知種別
    /// @param rSenderIP 送信者IPアドレス
    /// @param rReceiverIP 受信者IPアドレス
    /// @param nSendPort 送信ポート
    /// @param nReceivePort 受信ポート
    /// @param nProtocol プロトコル
    /// @return 自分宛てでない場合は0、通知を受け取った場合は1
    int NotificationReceived (TICMPNotificationType Type,
                  CIPAddress &rSenderIP, CIPAddress &rReceiverIP,
                  u16 nSendPort, u16 nReceivePort,
                  int nProtocol);

private:
    /// @brief セグメントを送信する
    /// @param nFlags フラグ
    /// @param nSequenceNumber シーケンス番号
    /// @param nAcknowledgmentNumber ACK番号
    /// @param pData データ
    /// @param nDataLength データ長
    /// @return
    boolean SendSegment (unsigned nFlags, u32 nSequenceNumber, u32 nAcknowledgmentNumber = 0,
                 const void *pData = 0, unsigned nDataLength = 0);
    /// @brief TCPヘッダオプションを解析する
    /// @param pHeader TCPヘッダ
    void ScanOptions (TTCPHeader *pHeader);
    /// @brief ISNを計算する
    /// @return ISN
    u32 CalculateISN (void);
    /// @brief タイマーを開始する
    /// @param nTimer 開始するタイマーのインデックス
    /// @param nHZ 遅延時間
    void StartTimer (unsigned nTimer, unsigned nHZ);
    /// @brief タイマーを停止する
    /// @param nTimer 停止するタイマーのインデックス
    void StopTimer (unsigned nTimer);
    /// @brief タイマーハンドラ
    /// @param nTimer 対象となるタイマーのインデックス
    void TimerHandler (unsigned nTimer);
    /// @brief タイマーハンドラスタブ
    /// @param hTimer タイマーハンドラ
    /// @param pParam 対象となるタイマーのインデックス
    /// @param pContext TCPコネクション
    static void TimerStub (TKernelTimerHandle hTimer, void *pParam, void *pContext);

#ifndef NDEBUG
    /// @brief 状態をログ出力
    void DumpStatus (void);
    /// @brief 状態を設定してログ出力
    /// @param State 設定する状態
    /// @param nLine ライン
    /// @return 状態
    TTCPState NewState (TTCPState State, unsigned nLine);
    /// @brief 状態エラーを出力
    /// @param nLine ライン
    void UnexpectedState (unsigned nLine);
#endif

private:
    /// @brief アクティブオープンか（FALSEはパッシブオープン）
    boolean     m_bActiveOpen;
    /// @brief TCP状態
    volatile TTCPState m_State;
    /// @brief エラー数
    volatile int m_nErrno;          // signalize error to the user
    /// @brief 送信キュー
    CNetQueue m_TxQueue;
    /// @brief 受信キュー
    CNetQueue m_RxQueue;
    /// @brief 再送キュー
    CRetransmissionQueue m_RetransmissionQueue;
    /// @brief 再送か
    volatile boolean m_bRetransmit; // reset m_RetransmissionQueue and send
    /// @brief SYN送信
    volatile boolean m_bSendSYN;    // TCPStateSynSent または TCPStateSynReceivedにある時SYSを送信する
    /// @brief FIN送信
    volatile boolean m_bFINQueued;  // 送信キューまたは再送キューがからの時FINを送信する
    /// @brief FIN送信後の状態
    TTCPState m_StateAfterFIN;      //  FIN送信後の状態

    /// @brief 再送回数
    volatile unsigned m_nRetransmissionCount;
    /// @brief タイムアウト
    volatile boolean m_bTimedOut;   // コネクションをアボートしてクローズ
    /// @brief イベント
    CSynchronizationEvent m_Event;
    /// @brief 送信イベント
    CSynchronizationEvent m_TxEvent;    // for pacing transmit
    /// @brief タイマー
    CTimer *m_pTimer;
    /// @brief タイマーの配列
    TKernelTimerHandle m_hTimer[TCPTimerUnknown];
    /// @brief タイマー配列を保護するスピンロック
    CSpinLock m_TimerSpinLock;

    //  送信シーケンス変数
    u32 m_nSND_UNA;     // send unacknowledged
    u32 m_nSND_NXT;     // send next
    u32 m_nSND_WND;     // send window
    u16 m_nSND_UP;      // send urgent pointer
    u32 m_nSND_WL1;     // segment sequence number used for last window update
    u32 m_nSND_WL2;     // segment acknowledgment number used for last window update
    u32 m_nISS;         // initial send sequence number

    // 受信シーケンス変数
    u32 m_nRCV_NXT;     // receive next
    u32 m_nRCV_WND;     // receive window
    //u16 m_nRCV_UP;    // receive urgent pointer
    u32 m_nIRS;         // initial receive sequence number

    // その他の変数
    u16 m_nSND_MSS;     // send maximum segment size
    /// @brief RTO計算器
    CRetransmissionTimeoutCalculator m_RTOCalculator;
    /// @brief コネクション数
    static unsigned s_nConnections;
};

#endif
