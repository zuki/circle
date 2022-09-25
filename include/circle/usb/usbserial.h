//
// usbserial.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2020  H. Kocevar <hinxx@protonmail.com>
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
#ifndef _circle_usb_usbserial_h
#define _circle_usb_usbserial_h

#include <circle/usb/usbfunction.h>
#include <circle/usb/usbendpoint.h>
#include <circle/numberpool.h>
#include <circle/types.h>

/**
 * @enum TUSBSerialDataBits
 * @brief シリアルデータビット数
 */
enum TUSBSerialDataBits
{
    USBSerialDataBits5      = 5,
    USBSerialDataBits6      = 6,
    USBSerialDataBits7      = 7,
    USBSerialDataBits8      = 8,
};

/**
 * @enum TUSBSerialStopBits
 * @brief シリアルストップビット数
 */
enum TUSBSerialStopBits
{
    USBSerialStopBits1      = 1,
    USBSerialStopBits2      = 2,
};

/**
 * @enum TUSBSerialParity
 * @brief シリアルパリティ
 */
enum TUSBSerialParity
{
    USBSerialParityNone     = 0,
    USBSerialParityOdd      = 1,
    USBSerialParityEven     = 2,
};

/**
 * @class CUSBSerialDevice
 * @brief シリアルデバイスを表すクラス
 */
class CUSBSerialDevice : public CUSBFunction
{
public:
    CUSBSerialDevice (CUSBFunction *pFunction,
              size_t nReadHeaderBytes = 0);        // 無視するバイト数
    virtual ~CUSBSerialDevice (void);

    boolean Configure (void);

    int Write (const void *pBuffer, size_t nCount);
    int Read (void *pBuffer, size_t nCount);

    /** ボーレート属性を設定 */
    virtual boolean SetBaudRate (unsigned nBaudRate);
    /** シリアルライン属性を設定 */
    virtual boolean SetLineProperties (TUSBSerialDataBits nDataBits, TUSBSerialParity nParity, TUSBSerialStopBits nStopBits);

private:
    void CompletionRoutine (CUSBRequest *pURB);
    static void CompletionStub (CUSBRequest *pURB, void *pParam, void *pContext);

protected:
    unsigned m_nBaudRate;                   /**< ボーレート */
    TUSBSerialDataBits m_nDataBits;         /**< データビット数 */
    TUSBSerialParity m_nParity;             /**< パリティ */
    TUSBSerialStopBits m_nStopBits;         /**< ストップビット長 */

private:
    size_t m_nReadHeaderBytes;              /**< 無視するバイト長 */

    CUSBEndpoint *m_pEndpointIn;            /**< IN用エンドポイント */
    CUSBEndpoint *m_pEndpointOut;           /**< OUT用エンドポイント */

    u8 *m_pBufferIn;                        /**< IN用バッファ */
    size_t m_nBufferInSize;                 /**< IN用バッファサイズ */
    size_t m_nBufferInValid;                /**< 不正バッファ */
    unsigned m_nBufferInPtr;                /**< バッファ内ポインタ */

    volatile boolean m_bInRequestActive;    /**< INリクエストがアクティブか */

    unsigned m_nDeviceNumber;               /**< デバイス番号 */
    static CNumberPool s_DeviceNumberPool;  /**< デバイス番号プール */
};

#endif
