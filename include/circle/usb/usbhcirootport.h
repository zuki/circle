//
// usbhcirootport.h
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
#ifndef _circle_usb_usbhcirootport_h
#define _circle_usb_usbhcirootport_h

#include <circle/types.h>

/// @brief USBホストコントローラのルートポートクラス
class CUSBHCIRootPort
{
public:
    /// @brief デストラクタ
    virtual ~CUSBHCIRootPort (void) {}
    /// @brief デバイスを再スキャン
    /// @return 操作の可否
    virtual boolean ReScanDevices (void) = 0;
    /// @brief デバイスの削除
    /// @return 操作の可否
    virtual boolean RemoveDevice (void) = 0;
    /// @brief ポートステータスの変更書を処理
    virtual void HandlePortStatusChange (void) = 0;

#if RASPPI >= 4
    virtual u8 GetPortID (void) const = 0;
#endif
};

#endif
