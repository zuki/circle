//
// usbhostcontroller.h
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
#ifndef _circle_usb_usbhostcontroller_h
#define _circle_usb_usbhostcontroller_h

#include <circle/usb/usb.h>
#include <circle/usb/usbendpoint.h>
#include <circle/usb/usbrequest.h>
#include <circle/ptrlist.h>
#include <circle/spinlock.h>
#include <circle/types.h>

// タイムアウトはインターラプトエンドポイントのみでサポートされる

#define USB_TIMEOUT_NONE    0    // Wait forever

class CUSBHCIRootPort;
class CUSBStandardHub;
class CUSBDevice;

/**
 * @class CUSBHostController
 * @brief USBホストコントローラを表すクラス
 */
class CUSBHostController
{
public:
    CUSBHostController (boolean bPlugAndPlay);
    virtual ~CUSBHostController (void);

    /**
     * ディスクリプタを取得する
     * @param pEndpoint エンドポイント
     * @param ucType ディスクリプタのタイプ
     * @param ucIndex インデックス
     * @param pBuffer バッファ
     * @param nBufSize バッファのサイズ
     * @param ucRequestType リクエストタイプ
     * @param wIndex エンドポイント、インタフェース、言語IDのいずれか
     * @return 長さ、失敗した場合は負値
     */
    int GetDescriptor (CUSBEndpoint *pEndpoint,
               unsigned char ucType, unsigned char ucIndex,
               void *pBuffer, unsigned nBufSize,
               unsigned char ucRequestType = REQUEST_IN,
               unsigned short wIndex = 0);        // endpoint, interface or language ID

    /**
     * デバイスアドレスをセット
     * @param pEndpoint エンドポイント
     * @param ucDeviceAddress デバイスアドレス
     * @return 成功したらTRUE, 失敗したらFALSE
     */
    boolean SetAddress (CUSBEndpoint *pEndpoint, u8 ucDeviceAddress);
    /**
     * コンフィグレーションをセット
     * @param pEndpoint エンドポイント
     * @param ucConfigurationValue コンフィグレーション値
     * @return 成功したらTRUE, 失敗したらFALSE
     */
    boolean SetConfiguration (CUSBEndpoint *pEndpoint, u8 ucConfigurationValue);

    /**
     * メッセージを送信する
     * @param pEndpoint エンドポイント
     * @param ucRequestType リクエストタイプ
     * @param ucRequest リクエスト
     * @param usValue 値
     * @param usIndex インデックス
     * @param pData データ
     * @param usDataSize データサイズ
     * @return 長さ、失敗した場合は負値
     */
    int ControlMessage (CUSBEndpoint *pEndpoint,
                u8 ucRequestType, u8 ucRequest, u16 usValue, u16 usIndex,
                void *pData, u16 usDataSize);

    /**
     * 転送する
     * @return 長さ、失敗した場合は負値
     */
    int Transfer (CUSBEndpoint *pEndpoint, void *pBuffer, unsigned nBufSize,
              unsigned nTimeoutMs = USB_TIMEOUT_NONE);

public:
    virtual boolean SubmitBlockingRequest (CUSBRequest *pURB,
                           unsigned nTimeoutMs = USB_TIMEOUT_NONE) = 0;

    virtual boolean SubmitAsyncRequest (CUSBRequest *pURB,
                        unsigned nTimeoutMs = USB_TIMEOUT_NONE) = 0;

    virtual void CancelDeviceTransactions (CUSBDevice *pUSBDevice) {}

public:
    static boolean IsPlugAndPlay (void);

    /**
     * デバイスツリーが更新されたか
     *
     * TASK_LEVELで呼び出す必要がある。
     * @return プラグアンドプレイが有効な場合、デバイスツリーが更新された場合
     *         TRUEを返す（最初に呼び出されたときは常にTRUEを返す）
     */
    boolean UpdatePlugAndPlay (void);

    static boolean IsActive (void)
    {
        return s_pThis != 0 ? TRUE : FALSE;
    }

    static CUSBHostController *Get (void);

protected:
    void PortStatusChanged (CUSBHCIRootPort *pRootPort);
    friend class CXHCIRootPort;

private:
    void PortStatusChanged (CUSBStandardHub *pHub);
    friend class CUSBStandardHub;

private:
    static boolean s_bPlugAndPlay;          //< プラグアンドプレイは有効か
    boolean m_bFirstUpdateCall;             //< 最初の更新呼び出しか

    CPtrList  m_HubList;                    //< ハブリスト
    CSpinLock m_SpinLock;                   //< スピンロック

    static CUSBHostController *s_pThis;     //< USBホストコントローラインスタンス
};

#endif
