//
/// \file serial.h
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
#ifndef _circle_serial_h
#define _circle_serial_h

#include <circle/device.h>
#include <circle/interrupt.h>
#include <circle/gpiopin.h>
#include <circle/spinlock.h>
#include <circle/sysconfig.h>
#include <circle/types.h>

/// \class CSerialDevice
/// \brief PL011 UARTドライバ
///
/// \details GPIO ピンマッピング（チップ番号）
/// nDevice | TXD    | RXD    | Support
/// :-----: | :----: | :----: | :------
/// 0       | GPIO14 | GPIO15 | すべてのボード
/// ^       | GPIO32 | GPIO33 | Compute Modules
/// ^       | GPIO36 | GPIO37 | Compute Modules
/// 1       |        |        | None (AUX)
/// 2       | GPIO0  | GPIO1  | Raspberry Pi 4 only
/// 3       | GPIO4  | GPIO5  | Raspberry Pi 4 only
/// 4       | GPIO8  | GPIO9  | Raspberry Pi 4 only
/// 5       | GPIO12 | GPIO13 | Raspberry Pi 4 only
/// GPIO32/33とGPIO36/37はシステムオプションSERIAL_GPIO_SELECTで選択できる。\n
/// GPIO0/1は通常、ID EEPROM用に予約されている。\n
/// ハンドシェークライン CTS と RTS はサポートされていない。

#if RASPPI < 4
    #define SERIAL_DEVICES      1
#else
    #define SERIAL_DEVICES      6
#endif

#define SERIAL_BUF_SIZE         2048                // 2のべき乗である必要ある
#define SERIAL_BUF_MASK         (SERIAL_BUF_SIZE-1)

// シリアルオプション
#define SERIAL_OPTION_ONLCR     (1 << 0)    ///< 出力時にNLをNL+CRに変換（デフォルト）

// Read/Write時に負値として返される
#define SERIAL_ERROR_BREAK      1
#define SERIAL_ERROR_OVERRUN    2
#define SERIAL_ERROR_FRAMING    3
#define SERIAL_ERROR_PARITY     4

class CSerialDevice : public CDevice
{
public:
    /// @brief パリティ
    enum TParity
    {
        ParityNone,
        ParityOdd,
        ParityEven,
        ParityUnknown
    };

public:
#ifndef USE_RPI_STUB_AT
    /// \brief コンストラクタ
    /// \param pInterruptSystem 割り込みシステムオブジェクトへのポインタ（ポーリングドライバの場合は0）
    /// \param bUseFIQ IRQではなくFIQを使用する
    /// \param nDevice デバイス番号（GPIO品マッピングを参照）
    CSerialDevice (CInterruptSystem *pInterruptSystem = 0, boolean bUseFIQ = FALSE,
               unsigned nDevice = 0);
    /// \brief デストラクタ
    ~CSerialDevice (void);
#endif
    /// \brief 初期化関数
    /// \param nBaudrate ボーレート（1秒あたりのビット数）
    /// \param nDataBits データビット数（5..8, デフォルトは 8）
    /// \param nStopBits ストップビット数（1..2, デフォルトは 1）
    /// \param Parity パリティ（ParityNone (デフォルト), ParityOdd, ParityEvenのいずれか）
    /// \return 操作は成功したか?
#ifndef USE_RPI_STUB_AT
    boolean Initialize (unsigned nBaudrate = 115200,
                unsigned nDataBits = 8, unsigned nStopBits = 1,
                TParity Parity = ParityNone);
#else
    boolean Initialize (unsigned nBaudrate = 115200);
#endif
    /// \brief データを送信する
    /// \param pBuffer 送信するデータへのポインタ
    /// \param nCount 送信するバイト数
    /// \return 送信に成功したバイト数（エラーの場合は負値）
    int Write (const void *pBuffer, size_t nCount);

#ifndef USE_RPI_STUB_AT
    /// \brief データを受信する
    /// \param pBuffer 受信データ用のバッファへのポインタ
    /// \param nCount 受信可能な最大バイト数
    /// \return 受信したバイト数（データなしは0、エラーの場合は負値）
    int Read (void *pBuffer, size_t nCount);
    /// \brief オプションを取得する
    /// \return シリアルオプションマスク（シリアルオプションを参照）
    unsigned GetOptions (void) const;
    /// \brief オプションを設定
    /// \param nOptions Serial シリアルオプションマスク（シリアルオプションを参照）
    void SetOptions (unsigned nOptions);

    typedef void TMagicReceivedHandler (void);
    /// \brief マジック文字列とそのハンドラを登録する
    /// \param pMagic 受信データ内で検索する文字列\n
    /// （このメソッドから帰った後もvalidでなければならない）
    /// \param pHandler マジック文字列が見つかった場合に呼び出されるハンドラ
    /// \note 割り込みドライバの場合にのみ動作する
    void RegisterMagicReceivedHandler (const char *pMagic, TMagicReceivedHandler *pHandler);

protected:
    /// \brief 使用可能なバッファスペースのバイト数を返す
    /// \return Write()で使用可能なバッファスペースのバイト数
    /// \note 割り込みドライバの場合にのみ動作する
    unsigned AvailableForWrite (void);

    /// \brief 使用可能な受信済みのバイト数を返す
    /// \return Read()で使用可能な受信済みのバイト数
    /// \note 割り込みドライバの場合にのみ動作する
    unsigned AvailableForRead (void);

    /// \brief 次の受信データを覗き見る
    /// \return Read()により返される次の受信バイト（データがない場合は-1）
    /// \note 割り込みドライバの場合にのみ動作する
    int Peek (void);

    /// \brief 送信データがすべて送信されるまで待機する
    void Flush (void);

private:
    /// @brief 1文字送信する
    /// @param uchChar 送信文字
    /// @return 送信の成否
    boolean Write (u8 uchChar);
    /// @brief 割り込みを処理する
    void InterruptHandler (void);
    /// @brief 割り込みを処理する
    static void InterruptStub (void *pParam);

private:
    CInterruptSystem *m_pInterruptSystem;
    boolean  m_bUseFIQ;
    unsigned m_nDevice;
    uintptr  m_nBaseAddress;
    boolean  m_bValid;

#if SERIAL_GPIO_SELECT == 14
    CGPIOPin m_GPIO32;
    CGPIOPin m_GPIO33;
#endif
    CGPIOPin m_TxDPin;
    CGPIOPin m_RxDPin;

    u8 m_RxBuffer[SERIAL_BUF_SIZE];
    volatile unsigned m_nRxInPtr;
    volatile unsigned m_nRxOutPtr;
    volatile int m_nRxStatus;

    u8 m_TxBuffer[SERIAL_BUF_SIZE];
    volatile unsigned m_nTxInPtr;
    volatile unsigned m_nTxOutPtr;

    unsigned m_nOptions;

    const char *m_pMagic;
    const char *m_pMagicPtr;
    TMagicReceivedHandler *m_pMagicReceivedHandler;

    CSpinLock m_SpinLock;
    CSpinLock m_LineSpinLock;

    static unsigned s_nInterruptUseCount;
    static CInterruptSystem *s_pInterruptSystem;
    static boolean s_bUseFIQ;
    static volatile u32 s_nInterruptDeviceMask;
    static CSerialDevice *s_pThis[SERIAL_DEVICES];
#endif
};

#endif
