//
// usbstandardhub.h
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
#ifndef _circle_usb_usbstandardhub_h
#define _circle_usb_usbstandardhub_h

#include <circle/usb/usb.h>
#include <circle/usb/usbhub.h>
#include <circle/usb/usbfunction.h>
#include <circle/usb/usbendpoint.h>
#include <circle/usb/usbdevice.h>
#include <circle/usb/usbhostcontroller.h>
#include <circle/numberpool.h>
#include <circle/types.h>

/// @brief USB標準ハブを表すクラス
class CUSBStandardHub : public CUSBFunction
{
public:
    /// @brief コンストラクタ
    /// @param pFunction USB機能クラスオブジェクト
    CUSBStandardHub (CUSBFunction *pFunction);
    /// @brief デストラクタ
    ~CUSBStandardHub (void);
    /// @brief 初期化関数
    /// @return 処理の成否
    boolean Initialize (void);
    /// @brief Configureを実行する
    /// @return 処理の成否
    boolean Configure (void);
    /// @brief デバイスの再スキャン
    /// @return 処理の成否
    boolean ReScanDevices (void);
    /// @brief ポートを無効にして、接続されていたデバイスを削除
    /// @param nPortIndex 削除するでバスが接続されていたポート番号
    /// @return 処理の成否
    boolean RemoveDevice (unsigned nPortIndex);    // nPortIndex is 0-based
    /// @brief ポートを無効にする
    /// @param nPortIndex 無効にするポート番号
    /// @return 処理の成否
    boolean DisablePort (unsigned nPortIndex);    // nPortIndex is 0-based

#if RASPPI >= 4
    const TUSBHubInfo *GetHubInfo (void) const;
#endif

private:
    /// @brief ポートをエニュメレート
    /// @return 処理の成否
    boolean EnumeratePorts (void);
    /// @brief ステータス変更リクエストを発行
    /// @return 処理の成否
    boolean StartStatusChangeRequest (void);
    /// @brief 処理完了コールバック
    /// @param pURB リクエストオブジェクトへのポインタ
    void CompletionRoutine (CUSBRequest *pURB);
    /// @brief 処理完了コールバックスタブ
    /// @param pURB リクエストオブジェクトへのポインタ
    /// @param pParam パラメタ（未使用）
    /// @param pContext コンテキスト（時オブジェクト）
    static void CompletionStub (CUSBRequest *pURB, void *pParam, void *pContext);
    /// @brief ポートステータスの変更を処理
    void HandlePortStatusChange (void);
    friend class CUSBHostController;

private:
    /// @brief ハブディスクリプタ
    TUSBHubDescriptor  *m_pHubDesc;
    /// @brief 割り込みエンドポイント
    CUSBEndpoint       *m_pInterruptEndpoint;
    /// @brief ステータス変更データ用のバッファ
    u8 *m_pStatusChangeBuffer;
    /// @brief ポート数
    unsigned            m_nPorts;
    /// @brief 電源オンか
    boolean             m_bPowerIsOn;
    /// @brief ポートデバイス配列
    CUSBDevice *m_pDevice[USB_HUB_MAX_PORTS];
    /// @brief ポートステータス配列
    TUSBPortStatus *m_pStatus[USB_HUB_MAX_PORTS];
    /// @brief ポット構成済み配列
    boolean m_bPortConfigured[USB_HUB_MAX_PORTS];

#if RASPPI >= 4
    TUSBHubInfo *m_pHubInfo;
#endif
    /// @brief デバイス番号
    unsigned            m_nDeviceNumber;
    /// @brief デバイス番号プール
    static CNumberPool  s_DeviceNumberPool;
};

#endif
