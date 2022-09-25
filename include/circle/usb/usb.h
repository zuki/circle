//
// usb.h
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
#ifndef _circle_usb_usb_h
#define _circle_usb_usb_h

#include <circle/macros.h>
#include <circle/usb/usbaudio.h>

/**
 * @enum TUSBPID
 * PID
 */
enum TUSBPID
{
    USBPIDSetup,
    USBPIDData0,
    USBPIDData1,
    //USBPIDData2,
    //USBPIDMData
};

// Device Addresses
#define USB_DEFAULT_ADDRESS             0
#define USB_FIRST_DEDICATED_ADDRESS     1
#define USB_MAX_ADDRESS                 63    // normally 127

/**
 * @enum TUSBSpeed
 * @brief 速度
 */
enum TUSBSpeed
{
    USBSpeedLow,
    USBSpeedFull,
    USBSpeedHigh,
    USBSpeedSuper,
    USBSpeedUnknown
};

/**
 * @enum TUSBError
 * @brief エラー
 */
enum TUSBError
{
    USBErrorStall,
    USBErrorTransaction,
    USBErrorBabble,
    USBErrorFrameOverrun,
    USBErrorDataToggle,
    USBErrorHostBus,
    USBErrorSplit,
    USBErrorTimeout,
    USBErrorAborted,
    USBErrorUnknown
};

/**
 * @struct  SetupData
 * @brief セットアップデータ（リクエスト構造体の共通部分）を表す構造体
 */
struct TSetupData
{
    unsigned char       bmRequestType;
    unsigned char       bRequest;
    unsigned short      wValue;
    unsigned short      wIndex;
    unsigned short      wLength;
    // Data follows
}
PACKED;

// Request Types
#define REQUEST_OUT             0
#define REQUEST_IN              0x80

#define REQUEST_CLASS           0x20
#define REQUEST_VENDOR          0x40

#define REQUEST_TO_DEVICE       0
#define REQUEST_TO_INTERFACE    1
#define REQUEST_TO_ENDPOINT     2
#define REQUEST_TO_OTHER        3

// Standard Request Codes
#define GET_STATUS              0
#define CLEAR_FEATURE           1
#define SET_FEATURE             3
#define SET_ADDRESS             5
#define GET_DESCRIPTOR          6
#define SET_CONFIGURATION       9
#define SET_INTERFACE           11

// Standard Feature Selectors
#define ENDPOINT_HALT           0

// Descriptor Types
#define DESCRIPTOR_DEVICE           1
#define DESCRIPTOR_CONFIGURATION    2
#define DESCRIPTOR_STRING           3
#define DESCRIPTOR_INTERFACE        4
#define DESCRIPTOR_ENDPOINT         5

// Class-specific descriptors
#define DESCRIPTOR_CS_INTERFACE     36
#define DESCRIPTOR_CS_ENDPOINT      37

#define DESCRIPTOR_INDEX_DEFAULT    0

/**
 * @struct TUSBDeviceDescriptor
 * @brief デバイス・ディスクリプタ構造体
 */
struct TUSBDeviceDescriptor
{
    unsigned char   bLength;
    unsigned char   bDescriptorType;
    unsigned short  bcdUSB;
    unsigned char   bDeviceClass;
    unsigned char   bDeviceSubClass;
    unsigned char   bDeviceProtocol;
    unsigned char   bMaxPacketSize0;
    #define USB_DEFAULT_MAX_PACKET_SIZE    8
    unsigned short  idVendor;
    unsigned short  idProduct;
    unsigned short  bcdDevice;
    unsigned char   iManufacturer;
    unsigned char   iProduct;
    unsigned char   iSerialNumber;
    unsigned char   bNumConfigurations;
}
PACKED;

/**
 * @struct TUSBConfigurationDescriptor
 * @brief コンフィギュレーション・ディスクリプタ構造体
 */
struct TUSBConfigurationDescriptor
{
    unsigned char   bLength;
    unsigned char   bDescriptorType;
    unsigned short  wTotalLength;
    unsigned char   bNumInterfaces;
    unsigned char   bConfigurationValue;
    unsigned char   iConfiguration;
    unsigned char   bmAttributes;
    unsigned char   bMaxPower;
}
PACKED;

/**
 * @struct TUSBInterfaceDescriptor
 * @brief インタフェース・ディスクリプタ構造体
 */
struct TUSBInterfaceDescriptor
{
    unsigned char    bLength;
    unsigned char    bDescriptorType;
    unsigned char    bInterfaceNumber;
    unsigned char    bAlternateSetting;
    unsigned char    bNumEndpoints;
    unsigned char    bInterfaceClass;
    unsigned char    bInterfaceSubClass;
    unsigned char    bInterfaceProtocol;
    unsigned char    iInterface;
}
PACKED;

/**
 * @struct TUSBEndpointDescriptor
 * @brief エンドポイント・ディスクリプタ構造体
 */
struct TUSBEndpointDescriptor
{
    unsigned char   bLength;
    unsigned char   bDescriptorType;
    unsigned char   bEndpointAddress;
    unsigned char   bmAttributes;
    unsigned short  wMaxPacketSize;
    unsigned char   bInterval;
}
PACKED;

/**
 * @union TUSBDescriptor
 * @brief USBディスクリプタを表すUNION
 */
union TUSBDescriptor
{
    struct
    {
        unsigned char    bLength;
        unsigned char    bDescriptorType;
    }
    Header;

    TUSBConfigurationDescriptor         Configuration;
    TUSBInterfaceDescriptor             Interface;
    TUSBEndpointDescriptor              Endpoint;

    TUSBAudioEndpointDescriptor         AudioEndpoint;
    TUSBMIDIStreamingEndpointDescriptor MIDIStreamingEndpoint;
}
PACKED;

/**
 * @struct TUSBStringDescriptor
 * @brief ストリング・ディスクリプタ構造体
 */
struct TUSBStringDescriptor
{
    unsigned char    bLength;
    unsigned char    bDescriptorType;
    unsigned short   bString[0];
}
PACKED;

#endif
