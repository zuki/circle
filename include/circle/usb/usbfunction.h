//
// usbfunction.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2019  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_usb_usbfunction_h
#define _circle_usb_usbfunction_h

#include <circle/device.h>
#include <circle/usb/usbconfigparser.h>
#include <circle/usb/usb.h>
#include <circle/usb/usbhub.h>
#include <circle/string.h>
#include <circle/types.h>

class CUSBDevice;
class CUSBHostController;
class CUSBEndpoint;

/**
 * @class CUSBFunction
 * @brief デバイス機能クラスを表すクラス
 */
class CUSBFunction : public CDevice
{
public:
    /**
     * @brief コンストラクタ
     * @param pDevice USBデバイスへのポインタ
     * @param pConfigParser コンフィグレーションパーサへのポインタ
     */
    CUSBFunction (CUSBDevice *pDevice, CUSBConfigurationParser *pConfigParser);
    /// @brief コピーコンストラクタ
    /// @param pFunction デバイス機能クラスオブジェクトへのポインタ
    CUSBFunction (CUSBFunction *pFunction);
    /// @brief デストラクタ
    virtual ~CUSBFunction (void);

    /// @brief 初期化関数
    virtual boolean Initialize (void);
    /// @brief コンフィグレーションを実行
    virtual boolean Configure (void);
    /// @brief デバイスを再スキャン
    virtual boolean ReScanDevices (void);
    /// @brief デバイスを削除
    virtual boolean RemoveDevice (void);
    /// @brief インタフェース名を取得。\n
    /// 文字列はcallerが削除
    /// @return インタフェース名文字列("intx-x-x"形式)
    CString *GetInterfaceName (void) const;
    /// @brief エンドポイント番号を取得
    /// @return エンドポイント番号
    u8 GetNumEndpoints (void) const;
    /// @brief デバイスを取得
    /// @return デバイスオブジェクトへのポインタ
    CUSBDevice *GetDevice (void) const;
    /// @brief デフォルトエンドポイントEP0を取得
    /// @return デフォルトエンドポイントへのポインタ
    CUSBEndpoint *GetEndpoint0 (void) const;
    /// @brief ホストコントローラを取得
    /// @return ホストコントローラへのポインタ
    CUSBHostController *GetHost (void) const;

    /// @brief 指定したタイプのディスクリプタを取得する
    /// @param ucType ディスクリプタタイプ
    /// @return ディスクリプタへのポインタ。見つからない場合は0
    const TUSBDescriptor *GetDescriptor (u8 ucType);
    /// @brief エラーをログ出力する
    /// @param pSource エラー元
    void ConfigurationError (const char *pSource) const;

    /// @brief タイプ、サブタイプ、プロトコルの3つ組を持つインタフェースがあるか調べる。\n
    /// デバイスがベンダID/製品IDで検知された場合、派生クラスのコンストラクタから呼び出される。
    /// @param uchClass クラス
    /// @param uchSubClass サブクラス
    /// @param uchProtocol プロトコル
    /// @return あればTURE、なければFALSE
    boolean SelectInterfaceByClass (u8 uchClass, u8 uchSubClass, u8 uchProtocol);

    /// @brief インタフェース番号を取得
    /// @return インタフェース番号
    u8 GetInterfaceNumber (void) const;
    /// @brief インタフェースのクラスを取得
    /// @return インタフェースのクラス
    u8 GetInterfaceClass (void) const;
    /// @brief インタフェースのサブクラスを取得
    /// @return インタフェースのサブクラス
    u8 GetInterfaceSubClass (void) const;
    /// @brief インタフェースのプロトコルを取得
    /// @return インタフェースのプロトコル
    u8 GetInterfaceProtocol (void) const;

#if RASPPI >= 4
    // returns 0 if this is not a hub function
    virtual const TUSBHubInfo *GetHubInfo (void) const    { return 0; }
#endif

private:
    /// @brief デバイス
    CUSBDevice              *m_pDevice;
    /// @brief コンフィグレーションパーサ
    CUSBConfigurationParser *m_pConfigParser;
    /// @brief いんたエースディスクリプタ
    TUSBInterfaceDescriptor *m_pInterfaceDesc;
};

#endif
