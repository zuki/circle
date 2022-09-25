//
// usbhub.h
//
// Definitions for USB hubs
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
#ifndef _circle_usb_usbhub_h
#define _circle_usb_usbhub_h

#include <circle/macros.h>
#include <circle/types.h>

// 構成
#define USB_HUB_MAX_PORTS       8        // TODO

// デバイスクラス
#define USB_DEVICE_CLASS_HUB    9

// クラス固有のリクエスト
#define RESET_TT                9

// ディスクリプタ種別
#define DESCRIPTOR_HUB          0x29

// 機能セレクタ
#define PORT_ENABLE             1
#define PORT_RESET              4
#define PORT_POWER              8
#define C_PORT_CONNECTION       16
#define C_PORT_ENABLE           17
#define C_PORT_SUSPEND          18
#define C_PORT_OVER_CURRENT     19
#define C_PORT_RESET            20

/**
 * @struct TUSBHubDescriptor
 * @brief ハブディスクリプタ構造体
 */
struct TUSBHubDescriptor
{
    unsigned char   bDescLength;                /**< ディスクリプタ長 */
    unsigned char   bDescriptorType;            /**< ディスクリプタ種別 */
    unsigned char   bNbrPorts;                  /**< ポート番号 */
    unsigned short  wHubCharacteristics;        /**< ハブ特性 */
        #define HUB_POWER_MODE(reg)             ((reg) & 3)
            #define HUB_POWER_MODE_GANGED       0
            #define HUB_POWER_MODE_INDIVIDUAL   1
        #define HUB_TT_THINK_TIME(reg)          (((reg) >> 5) & 3)
    unsigned char   bPwrOn2PwrGood;             /**< 電源オンから電源が安定するまで */
    unsigned char   bHubContrCurrent;           /**< ハブ電流制御 */
    unsigned char   DeviceRemoveable[1];        /**< リムーバルデバイス（最大8ポート） */
    unsigned char   PortPwrCtrlMask[1];         /**< ポートパワー制御マスク（最大8ポート） */
}
PACKED;

/**
 * @struct TUSBHubStatus
 * @brief ハブステータス構造体
 */
struct TUSBHubStatus
{
    unsigned short    wHubStatus;
        #define HUB_LOCAL_POWER_LOST__MASK      (1 << 0)
        #define HUB_OVER_CURRENT__MASK          (1 << 1)
    unsigned short    wHubChange;
        #define C_HUB_LOCAL_POWER_LOST__MASK    (1 << 0)
        #define C_HUB_OVER_CURRENT__MASK        (1 << 1)
}
PACKED;

/**
 * @struct TUSBPortStatus
 * @brief ポートステータス構造体
 */
struct TUSBPortStatus
{
    unsigned short    wPortStatus;
        #define PORT_CONNECTION__MASK           (1 << 0)
        #define PORT_ENABLE__MASK               (1 << 1)
        #define PORT_OVER_CURRENT__MASK         (1 << 3)
        #define PORT_RESET__MASK                (1 << 4)
        #define PORT_POWER__MASK                (1 << 8)
        #define PORT_LOW_SPEED__MASK            (1 << 9)
        #define PORT_HIGH_SPEED__MASK           (1 << 10)
    unsigned short    wChangeStatus;
        #define C_PORT_CONNECTION__MASK         (1 << 0)
        #define C_PORT_ENABLE__MASK             (1 << 1)
        #define C_PORT_SUSPEND__MASK            (1 << 2)
        #define C_PORT_OVER_CURRENT__MASK       (1 << 3)
        #define C_PORT_RESET__MASK              (1 << 4)
}
PACKED;

#if RASPPI >= 4

struct TUSBHubInfo
{
    unsigned    NumberOfPorts;
    boolean        HasMultipleTTs;
    u8        TTThinkTime;
};

#endif

#endif
