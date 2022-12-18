/** @addtogroup net_core
 *  @{
 */
//
// netsocket.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2018  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_net_netsocket_h
#define _circle_net_netsocket_h

#include <circle/net/ipaddress.h>
#include <circle/types.h>

class CNetSubSystem;

/// @brief ネットワークソケットの基底クラス
class CNetSocket
{
public:
    /// \brief コンストラクタ
    /// \param pNetSubSystem ネットワークサブシステムへのポインタ
    CNetSocket (CNetSubSystem *pNetSubSystem);

    /// \brief デストラクタ（アクティブコネクションを終了させる）
    virtual ~CNetSocket (void);

    /// \brief 自身のポート番号をこのソケットにバインドする
    /// \param nOwnPort ポート番号
    /// \return ステータス (0 成功, < 0 エラー)
    virtual int Bind (u16 nOwnPort) { return -1; }

    /// \brief 外部のホスト/ポートに接続する（TCP）、外部のホスト/ポートアドレスを設定する（UDP）
    /// \param rForeignIP 接続するホストのIPアドレス
    /// \param nForeignPort   接続するポート番号
    /// \return ステータス (0 成功, < 0 エラー)
    virtual int Connect (CIPAddress &rForeignIP, u16 nForeignPort) = 0;

    /// \brief 外部のホスト/ポートに接続する（TCP）、外部のホスト/ポートアドレスを設定する（UDP）
    /// \param pHost 接続するホストのホスト名またはIPアドレス文字列
    /// \param pPort 接続するポートの10進数文字列
    /// \return ステータス (0 成功, < 0 エラー)
    virtual int Connect (const char *pHost, const char *pPort);

    /// \brief 接続されるのを待つ（TCPのみ、先にBlind()を呼び出す必要がある）
    /// \param nBackLog Accept()が呼ばれる前に連続して受付可能な最大同時接続数
    /// \return ステータス (0 成功, < 0 エラー)
    virtual int Listen (unsigned nBackLog)  { return -1; }
    /// \brief 接続を受け付ける（TCPのみ、先にListen()を呼び出す必要がある）
    /// \param pForeignIP    リモートホストのIPアドレスはここに返される
    /// \param pForeignPort    リモートポート番号は個々に返される
    /// \return リモートホストとの通信に使用される新しく作成されたソケット（エラーの場合は0）
    virtual CNetSocket *Accept (CIPAddress *pForeignIP, u16 *pForeignPort) { return 0; }

    /// \brief リモートホストにメッセージを送信する
    /// \param pBuffer メッセージへのポインタ
    /// \param nLength メッセージ長
    /// \param nFlags  MSG_DONTWAIT（ノンブロッキング操作）または 0（ブロッキング操作）
    /// \return 送信したメッセージ長（エラー時は< 0）
    virtual int Send (const void *pBuffer, unsigned nLength, int nFlags) = 0;

    /// \brief リモートホストからメッセージを受信する
    /// \param pBuffer メッセージバッファへのポインタ
    /// \param nLength メッセージバッファのサイズ（バイト単位）\n
    /// 少なくともFRAME_BUFFER_SIZEである必要がある。そうでないとソケットによってはデータが損失する場合がある
    /// \param nFlags MSG_DONTWAIT（ノンブロッキング操作）または 0（ブロッキング操作）
    /// \return 受信したメッセージ長（メッセージがなかった場合はMSG_DONTWAITで0、エラー時は < 0）
    virtual int Receive (void *pBuffer, unsigned nLength, int nFlags) = 0;

    /// \brief 指定のリモートホストにメッセージを送信する
    /// \param pBuffer    メッセージへのポインタ
    /// \param nLength    メッセージ長
    /// \param nFlags    MSG_DONTWAIT（ノンブロッキング操作）または 0（ブロッキング操作）
    /// \param rForeignIP    送信先ホストのIPアドレス（TCPソケットでは無視される）
    /// \param nForeignPort    送信先のポート番号（TCPソケットでは無視される）
    /// \return 送信したメッセージ長（エラー時は< 0）
    virtual int SendTo (const void *pBuffer, unsigned nLength, int nFlags,
                CIPAddress &rForeignIP, u16 nForeignPort) { return -1; }

    /// \brief リモートホストからメッセージを受信し、リモートホストのホスト/ポートを返す
    /// \param pBuffer メッセージバッファへのポインタ
    /// \param nLength メッセージバッファのサイズ（バイト単位）\n
    /// 少なくともFRAME_BUFFER_SIZEである必要がある。そうでないとソケットによってはデータが損失する場合がある
    /// \param nFlags MSG_DONTWAIT（ノンブロッキング操作）または 0（ブロッキング操作）
    /// \param pForeignIP    メッセージを送信したホストのIPアドレスがここに返される
    /// \param pForeignPort    メッセージを送信したポート番号がここに返される
    /// \return 受信したメッセージ長（メッセージがなかった場合はMSG_DONTWAITで0、エラー時は < 0）
    virtual int ReceiveFrom (void *pBuffer, unsigned nLength, int nFlags,
                 CIPAddress *pForeignIP, u16 *pForeignPort) { return -1; }

    /// \brief Bind()またはConnect()の後にbAllowed == TRUEで呼び出すと\n
    /// ブロードキャストメッセージを送受信できる（TCPソケットでは無視される）
    /// \param bAllowed ブロードキャスの送受信はこのソケットでは許されるか（デフォルトはFALSE）
    /// \return ステータス (0 成功, < 0 エラー)
    virtual int SetOptionBroadcast (boolean bAllowed) { return -1; }

    /// \brief 接続したリモートホストのIPアドレスを取得する
    /// \return IPアドレスへのポインタ（4バイト、接続されていない場合はポインタ0）
    virtual const u8 *GetForeignIP (void) const = 0;

protected:
    /// @brief ネットサブシステムを取得する
    /// @return ネットサブシステムオブジェクトへのポインタ
    CNetSubSystem *GetNetSubSystem (void);

private:
    /// @brief ネットサブシステムオブジェクトへのポインタ
    CNetSubSystem *m_pNetSubSystem;
};

/** @} */

#endif
