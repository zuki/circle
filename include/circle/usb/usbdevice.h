//
// usbdevice.h
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
#ifndef _circle_usb_usbdevice_h
#define _circle_usb_usbdevice_h

#include <circle/usb/usb.h>
#include <circle/usb/usbconfigparser.h>
#include <circle/usb/usbfunction.h>
#include <circle/numberpool.h>
#include <circle/logger.h>
#include <circle/string.h>
#include <circle/types.h>

#define USBDEV_MAX_FUNCTIONS    10

/**
 * @enum TDeviceNameSelector
 * @brief デバイス名セレクタ
 */
enum TDeviceNameSelector        // do not change this order
{
    DeviceNameVendor,
    DeviceNameDevice,
    DeviceNameUnknown
};

class CUSBHostController;
class CUSBHCIRootPort;
class CUSBStandardHub;
class CUSBEndpoint;

/**
 * @class CUSBDevice
 * @brief USBデバイスを表すクラス
 */
class CUSBDevice
{
public:
    /** コンストラクタ1 */
    CUSBDevice (CUSBHostController *pHost, TUSBSpeed Speed, CUSBHCIRootPort *pRootPort);
    /** コンストラクタ2 */
    CUSBDevice (CUSBHostController *pHost, TUSBSpeed Speed,
            CUSBStandardHub *pHub, unsigned nHubPortIndex);
    /** デストラクタ */
    virtual ~CUSBDevice (void);
    //! 初期化
    virtual boolean Initialize (void);  // アドレスステートに（フェーズ1）
    //! 構成
    virtual boolean Configure (void);   // 構成済ステートに（フェース2）

    /** デバイス再スキャン */
    boolean ReScanDevices (void);
    /** デバイス削除 */
    boolean RemoveDevice (void);
    /** 名前を取得 */
    CString *GetName (TDeviceNameSelector Selector) const;  // 文字列はcallerが削除
    /** 名前をすべて取得 */
    CString *GetNames (void) const;                         // 文字列はcallerが削除
    /** アドレスを取得 */
    u8 GetAddress (void) const;                             // xHCI: slot ID
    /** スピードを取得 */
    TUSBSpeed GetSpeed (void) const;
    /** スプリット転送か */
    boolean IsSplit (void) const;
    /** ハブのアドレスを取得 */
    u8 GetHubAddress (void) const;                          // xHCI: slot ID
    /** ハブのポート番号を取得 */
    u8 GetHubPortNumber (void) const;
    /** ハブのデバイスを取得 */
    CUSBDevice *GetTTHubDevice (void) const;
    /** エンドポイント0を取得 */
    CUSBEndpoint *GetEndpoint0 (void) const;
    /** ホストを取得 */
    CUSBHostController *GetHost (void) const;
    /** デバイスディスクリプタを取得 */
    const TUSBDeviceDescriptor *GetDeviceDescriptor (void) const;
    /** コンフィグレーションディスクリプタを取得 */
    const TUSBConfigurationDescriptor *GetConfigurationDescriptor (void) const; // デフォルトコンフィグ

    /** コンフィグレーションディスクリプタからucTypeの次のサブディスクリプタを取得 */
    const TUSBDescriptor *GetDescriptor (u8 ucType);        // 見つからない場合は0を返す
    /** コンフィグレーションエラー */
    void ConfigurationError (const char *pSource) const;
    /** ログ出力 */
    void LogWrite (TLogSeverity Severity, const char *pMessage, ...);

#if RASPPI >= 4
    virtual boolean EnableHubFunction (void) = 0;

    unsigned GetRootHubPortID (void) const  { return m_nRootHubPortID; }
    u32 GetRouteString (void) const         { return m_nRouteString; }

    // returns 0 if this is not a hub device
    const TUSBHubInfo *GetHubInfo (void) const
    {
        return m_pFunction[0] != 0 ? m_pFunction[0]->GetHubInfo () : 0;
    }
#endif

protected:
    /** アドレスをセット */
    void SetAddress (u8 ucAddress);        // xHCI: set slot ID

private:
#if RASPPI >= 4
    static u32 AppendPortToRouteString (u32 nRouteString, unsigned nPort);
#endif

private:
    CUSBHostController *m_pHost;            /**< ホストコントローラ */
    CUSBHCIRootPort    *m_pRootPort;        /**< このデバイスが接続されるルートポート */
    CUSBStandardHub    *m_pHub;             /**< または、このデバイスが接続されるハブ */
    unsigned            m_nHubPortIndex;    /**< このハブの0ベースのインデックス */

    u8                  m_ucAddress;        /**< アドレス */
    TUSBSpeed           m_Speed;            /**< スピード */
    CUSBEndpoint       *m_pEndpoint0;       /**< エンドポイント0 */

    boolean             m_bSplitTransfer;   /**< 分割転送か */
    u8                  m_ucHubAddress;     /**< ハブアドレス */
    u8                  m_ucHubPortNumber;  /**< ハブポート番号 */
    CUSBDevice         *m_pTTHubDevice;     /**< ハブデバイス */

    TUSBDeviceDescriptor        *m_pDeviceDesc;         /**< デバイスディスクリプタ */
    TUSBConfigurationDescriptor *m_pConfigDesc;         /**< コンフィグレーションディスクリプタ*/

    CUSBConfigurationParser     *m_pConfigParser;       /**< コンフィグレーションパーサ */

    CUSBFunction *m_pFunction[USBDEV_MAX_FUNCTIONS];    /**< デバイスクラス */

#if RASPPI >= 4
    unsigned m_nRootHubPortID;
    u32     m_nRouteString;
#endif

#if RASPPI <= 3
    static CNumberPool s_DeviceAddressPool;             /**< デバイスアドレスプール */
#endif
};

#endif
