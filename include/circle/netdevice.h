//
// netdevice.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2020  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_netdevice_h
#define _circle_netdevice_h

#include <circle/macaddress.h>
#include <circle/types.h>

#define FRAME_BUFFER_SIZE    1600

#define MAX_NET_DEVICES        5

/// @brief ネットデバイスタイプ
enum TNetDeviceType
{
    NetDeviceTypeEthernet,
    NetDeviceTypeWLAN,
    NetDeviceTypeAny,
    NetDeviceTypeUnknown
};

/// @brief ネットデバイススピード
enum TNetDeviceSpeed
{
    NetDeviceSpeed10Half,
    NetDeviceSpeed10Full,
    NetDeviceSpeed100Half,
    NetDeviceSpeed100Full,
    NetDeviceSpeed1000Half,
    NetDeviceSpeed1000Full,
    NetDeviceSpeedUnknown
};

/// @brief ネットデバイスの基底クラス（インタフェース）
class CNetDevice
{
public:
    virtual ~CNetDevice (void) {}

    /// \brief このネットデバイスの種別を取得する
    /// \return ネットデバイスの種別
    virtual TNetDeviceType GetType (void)        { return NetDeviceTypeEthernet; }

    /// \brief MACアドレスを取得する
    /// \return 自身のアドレスを保持するMACアドレスオブジェクトへのポインタ
    virtual const CMACAddress *GetMACAddress (void) const = 0;

    /// \brief SendFrame()を呼び出しが望ましいかのヒントを与える
    /// \return SendFrame()を呼び出しが望ましい場合にRUE
    /// \note SendFrame()はいつでも呼び出せるが、TXキューがフルの場合は失敗する。\n
    ///      このメソッドはSendFrame()の呼び出しが望ましいか田舎についてのヒントを与える。
    virtual boolean IsSendFrameAdvisable (void)    { return TRUE; }

    /// \brief ネットワークに正しいEthernetフレームを送信する
    /// \param pBuffer フレームへのポインタ。FCSは含まない
    /// \param nLength バイト単位のフレーム長。パディングは不要
    virtual boolean SendFrame (const void *pBuffer, unsigned nLength) = 0;

    /// \brief Ethernetフレームを受信するまでポーリング
    /// \param pBuffer フレームはここに置かれる。FRAME_BUFFER_SIZEサイズのバッファでなければならない
    /// \param pResultLength 正しいフレーム帳を受け取る変数へのポインタ
    /// \return フレームがバッファに返された場合はTRUE、何も受信しなかった場合はFALSE
    virtual boolean ReceiveFrame (void *pBuffer, unsigned *pResultLength) = 0;

    /// \brief PHYはupか
    /// \return PHYがupの場合にTRUE
    virtual boolean IsLinkUp (void)            { return TRUE; }

    /// \brief ィン区スピードを取得する
    /// \return PHYリンクのスピード（upの場合）
    virtual TNetDeviceSpeed GetLinkSpeed (void)    { return NetDeviceSpeedUnknown; }

    /// \brief PHYステータスに従いデバイスセッテイングを更新する
    /// \return サポートしていない場合はFALSE
    /// \note ネットPHYタスクにより２秒毎に呼び出される
    virtual boolean UpdatePHY (void)        { return FALSE; }

    /// \brief スピード値に関する文字列を取得する
    /// \param Speed GetLinkSpeed()により返された値
    /// \return このスピード値に関する文字列
    static const char *GetSpeedString (TNetDeviceSpeed Speed);

    /// \brief 指定の番号のネットデバイスを取得する
    /// \param nDeviceNumber ネットデバイス番号（0始まり、通常、0だけが使用される）
    /// \return 出刃シスオブジェクトへのポインタ
    static CNetDevice *GetNetDevice (unsigned nDeviceNumber);

    /// \brief 指定した種別の最初のネットデバイスを取得する
    /// \param Type 検索する特定のネットデバイス種別（あるいはNetDeviceTypeAny）
    /// \return この種別の最初のデバイスオブジェクトへのポインタ
    static CNetDevice *GetNetDevice (TNetDeviceType Type);

protected:
    /// @brief このデバイスをネットデバイスとして登録する
    void AddNetDevice (void);

private:
    /// @brief デバイス番号
    static unsigned s_nDeviceNumber;
    /// @brief ネットデバイス登録配列
    static CNetDevice *s_pDevice[MAX_NET_DEVICES];
    /// @brief スピード不明を示す文字列
    static const char *s_SpeedString[NetDeviceSpeedUnknown];
};

#endif
