//
// lan7800.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2018-2019  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_usb_lan7800_h
#define _circle_usb_lan7800_h

#include <circle/netdevice.h>
#include <circle/usb/usbfunction.h>
#include <circle/usb/usbendpoint.h>
#include <circle/usb/usbrequest.h>
#include <circle/macaddress.h>
#include <circle/timer.h>
#include <circle/types.h>

/**
 * @class  CLAN7800Device
 * @brief LCAN7800 Ethernetコントローラを表すクラス
 */
class CLAN7800Device : public CUSBFunction, CNetDevice
{
public:
    /// \brief コンストラクタ
    /// \param pFunction デバイスクラスオブジェクトへのポインタ
    CLAN7800Device (CUSBFunction *pFunction);
    /// \brief デストラクタ
    ~CLAN7800Device (void);

    /// @brief 構成する
    /// @return 失敗したらFALSE
    boolean Configure (void);

    /// @brief MACアドレスを首都kする
    /// @return MACアドレスオブジェクトへのポインタ
    const CMACAddress *GetMACAddress (void) const;

    /// @brief フレームを送信する
    /// @param pBuffer バッファポインタ
    /// @param nLength バッファ長
    /// @return 失敗したらFALSE
    boolean SendFrame (const void *pBuffer, unsigned nLength);

    // pBuffer must have size FRAME_BUFFER_SIZE

    /// @brief フレームを受信する
    /// pBufferの長さはFRAME_BUFFER_SIZEでなければならない
    /// @param pBuffer バッファポインタ
    /// @param pResultLength バッファ読み込みサイズ
    /// @return 失敗したらFALSE
    boolean ReceiveFrame (void *pBuffer, unsigned *pResultLength);

    /// @brief PHYリンクはupしているか
    /// @return upしていたらTRUE
    boolean IsLinkUp (void);

    /// @brief リンクスピードを取得する
    /// @return リンクスピード
    TNetDeviceSpeed GetLinkSpeed (void);

private:
    /// @brief MACアドレスを初期化する
    /// @return 失敗したらFALSE
    boolean InitMACAddress (void);
    /// @brief PHYを初期化する
    /// @return 失敗したらFALSE
    boolean InitPHY (void);

    /// @brief PHYに書き込み
    /// @param uchIndex インデックス
    /// @param usValue 書き込む値
    /// @return 失敗したらFALSE
    boolean PHYWrite (u8 uchIndex, u16 usValue);
    /// @brief PHYを読み込む
    /// @param uchIndex インデックス
    /// @param pValue 読み込んだ値を保管する変数のポインタ
    /// @return 失敗したらFALSE
    boolean PHYRead (u8 uchIndex, u16 *pValue);

    // wait until register 'nIndex' has value 'nCompare' with mask 'nMask' applied,
    // check the register each 'nDelayMicros' microseconds, timeout after 'nTimeoutHZ' ticks

    /// @brief レジスタnIndexをnMaskでマスクした値がnComapreになるのを待つ。
    /// nDelayMicrosマイクロ秒ごとにレジスタをチェックし、nTimeoutHZチック後にタイムアウトする
    /// @param nIndex レジスタ
    /// @param nMask マスク値
    /// @param nCompare 比較値
    /// @param nDelayMicros チェック間隔
    /// @param nTimeoutHZ 大雨アウト
    /// @return タイムアウトしたらFALSE
    boolean WaitReg (u32 nIndex, u32 nMask, u32 nCompare = 0,
             unsigned nDelayMicros = 1000, unsigned nTimeoutHZ = HZ);

    /// @brief レジスタ値を読み取り、nOrMaskとnAndMaskを適用して書き戻す
    /// @param nIndex レジスタ
    /// @param nOrMask ORマスク値
    /// @param nAndMask ANDマスク値
    /// @return 失敗したらFALSE
    boolean ReadWriteReg (u32 nIndex, u32 nOrMask, u32 nAndMask = ~0U);
    /// @brief レジスタに値を書き込む
    /// @param nIndex レジスタ
    /// @param nValue 書き込む値
    /// @return 失敗したらFALSE
    boolean WriteReg (u32 nIndex, u32 nValue);
    /// @brief レジスタを読む
    /// @param nIndex レジスタ
    /// @param pValue 読み込んだ値を保管する変数のポインタ
    /// @return
    boolean ReadReg (u32 nIndex, u32 *pValue);

private:
    /// @brief IN用のエンドポイント
    CUSBEndpoint *m_pEndpointBulkIn;
    /// @brief OUT用のエンドポイント
    CUSBEndpoint *m_pEndpointBulkOut;
    /// @brief MACアドレス
    CMACAddress m_MACAddress;
};

#endif
