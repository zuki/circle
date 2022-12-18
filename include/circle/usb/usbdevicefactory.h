/** @addtogroup usb_core
 *  @{
 */
//
// usbdevicefactory.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2021  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_usb_usbdevicefactory_h
#define _circle_usb_usbdevicefactory_h

#include <circle/usb/usbfunction.h>
#include <circle/string.h>
#include <circle/types.h>

#define USB_DEVICE(vendorid, deviceid)        vendorid, deviceid

/**
 * @struct TUSBDeviceID
 * @brief デバイスID構造体
 */
struct TUSBDeviceID
{
    u16    usVendorID;
    u16    usDeviceID;
};

/**
 * @class CUSBDeviceFactory
 * @brief USBデバイスファクトリクラス
 */
class CUSBDeviceFactory
{
public:
    /// @brief 指定のデバイス名またはインタフェース名のデバイスを取得する
    /// @param pParent 親デバイスオブジェクトへのポインタ
    /// @param pName インタフェース名(venxxx-xxx, intx-x-x)
    /// @return デバイスへのポインタ。見つからなかった場合は0
    static CUSBFunction *GetDevice (CUSBFunction *pParent, CString *pName);

private:
    /// @brief int3-0-0のデバイスからタッチパネルまたはゲームパッドデバイスを取得する
    /// @param pParent 親デバイスオブジェクトへのポインタ
    /// @return デバイスへのポインタ。見つからなかった場合は0
    static CUSBFunction *GetGenericHIDDevice (CUSBFunction *pParent);
    /// @brief デバイスIDテーブルで指定のデバイス名を検索する
    /// @param pName デバイス名
    /// @param pIDTable デバイスIDテーブル
    /// @return あればTRUE、なければFALSE
    static boolean FindDeviceID (CString *pName, const TUSBDeviceID *pIDTable);
};

/** @} */
#endif
