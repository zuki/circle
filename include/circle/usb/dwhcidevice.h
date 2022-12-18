/** @defgroup dwhc DesignWareホストコントローラ関連クラス
 *  @ingroup usb
 *  @{
 */
//
// dwhcidevice.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2022  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_usb_dwhcidevice_h
#define _circle_usb_dwhcidevice_h

#include <circle/usb/usbhostcontroller.h>
#include <circle/interrupt.h>
#include <circle/timer.h>
#include <circle/usb/usbendpoint.h>
#include <circle/usb/usbrequest.h>
#include <circle/usb/dwhcirootport.h>
#include <circle/usb/dwhcixferstagedata.h>
#include <circle/usb/dwhcixactqueue.h>
#include <circle/usb/dwhcicompletionqueue.h>
#include <circle/usb/dwhciregister.h>
#include <circle/usb/dwhci.h>
#include <circle/usb/usb.h>
#include <circle/spinlock.h>
#include <circle/mphi.h>
#include <circle/sysconfig.h>
#include <circle/types.h>

#define DWHCI_WAIT_BLOCKS    DWHCI_MAX_CHANNELS

/**
 * @class CDWHCIDevice
 * @brief DWHCI（DesignWare HS OTGコントローラ）デバイスを表すクラス
 */
class CDWHCIDevice : public CUSBHostController
{
public:
    /**
     * @brief コンストラクタ
     * @param pInterruptSystem  割り込みシステム
     * @param pTimer タイマー
     * @param bPlugAndPlay プラグアンドプレイの有無
     */
    CDWHCIDevice (CInterruptSystem *pInterruptSystem, CTimer *pTimer,
              boolean bPlugAndPlay = FALSE);
    ~CDWHCIDevice (void);

    /**
     * @brief DWHCデバイスの初期化
     * @param bScanDevices 初期化の最後にデバイスを再スキャンするか
     * @return 成功したらTRUE, 失敗したらFALSE
     */
    boolean Initialize (boolean bScanDevices = TRUE);

    /**
     * @brief ルートポートが初期化されていなかったら初期化してUSBデバイスが接続されていないかスキャン
     */
    void ReScanDevices (void);

    /**
     * リクエストをブロッキングモードで発行する（アイソクロナス転送は未サポート）
     * @param pURB リクエスト
     * @param nTimeoutMs タイムアウト時間（デフォルトは0: なし）
     * @return 成功したらTRUE, 失敗したらFALSE
     */
    boolean SubmitBlockingRequest (CUSBRequest *pURB, unsigned nTimeoutMs = USB_TIMEOUT_NONE);
    /// @brief リクエストを非同期に発行する（バルク転送とインタラプト転送のみ）
    /// @param pURB リクエスト
    /// @param nTimeoutMs タイムアウト時間（デフォルトは0: なし）
    /// @return 成功したらTRUE, 失敗したらFALSE
    boolean SubmitAsyncRequest (CUSBRequest *pURB, unsigned nTimeoutMs = USB_TIMEOUT_NONE);
    /// @brief 指定デバイスのトランザクションをキャンセルする
    /// @param pUSBDevice キャンセルするデバイス
    void CancelDeviceTransactions (CUSBDevice *pUSBDevice);

private:
    /// @brief ホストポートはコネクトされているか
    /// @return されていればTRUE
    boolean DeviceConnected (void);
    /// @brief ホストポートのスピードを取得する
    /// @return ホストスピード
    TUSBSpeed GetPortSpeed (void);
    /// @brief 過電流がないか
    /// @return 過電流があればTRUE
    boolean OvercurrentDetected (void);
    /// @brief ホストのルートポートを無効化して、電源を切る（bPowerOff = TRUEの場合）
    /// @param bPowerOff 電源を切るか
    void DisableRootPort (boolean bPowerOff = TRUE);
    friend class CDWHCIRootPort;

private:
    /// @brief コアの初期化
    /// @return 操作の成否
    boolean InitCore (void);
    /// @brief dwhcホストの初期化
    /// @return 常にTRUE
    boolean InitHost (void);
    /// @brief ルートポートの有効化
    /// @return 操作の成否
    boolean EnableRootPort (void);
    /// @brief dwhcホストの電源オン
    /// @return 操作の成否
    boolean PowerOn (void);
    /// @brief dwhcホストのリセット
    /// @return 操作の成否
    boolean Reset (void);
    /// @brief グローバル割り込みの有効化
    void EnableGlobalInterrupts (void);
    /// @brief 一般割り込みの有効化
    void EnableCommonInterrupts (void);
    /// @brief dwhcホスト割り込みの有効化
    void EnableHostInterrupts (void);
    /// @brief チャネル割り込みの有効化
    /// @param nChannel 有効にするチャネル番号
    void EnableChannelInterrupt (unsigned nChannel);
    /// @brief チャネル割り込みの無効化
    /// @param nChannel 無効にするチャネル番号
    void DisableChannelInterrupt (unsigned nChannel);
    /// @brief 送信FIFOのフラッシュ
    /// @param nFIFO FIFO番号
    void FlushTxFIFO (unsigned nFIFO);
    /// @brief 受信FIFOのフラッシュ
    void FlushRxFIFO (void);
    /// @brief リクエストの転送
    /// @param pURB USBリクエストオブジェクト
    /// @param bIn INリクエストか
    /// @param bStatusStage  ステータスステージか
    /// @param nTimeoutMs タイムアウト
    /// @return
    boolean TransferStage (CUSBRequest *pURB, boolean bIn, boolean bStatusStage,
                   unsigned nTimeoutMs = USB_TIMEOUT_NONE);
    /// @brief 転送完了処理
    /// @param pURB リクエスト
    /// @param pParam リクエストパラメタ
    /// @param pContext コンテキスト
    static void CompletionRoutine (CUSBRequest *pURB, void *pParam, void *pContext);
    /// @brief リクエストの非同期転送
    /// @param pURB USBリクエストオブジェクト
    /// @param bIn INリクエストか
    /// @param bStatusStage ステータスステージか
    /// @param nTimeoutMs タイムアウト
    /// @return
    boolean TransferStageAsync (CUSBRequest *pURB, boolean bIn, boolean bStatusStage,
                    unsigned nTimeoutMs = USB_TIMEOUT_NONE);

#ifdef USE_USB_SOF_INTR
    /// @brief トランザクションをキューに入れる
    /// @param pStageData トランザクションステージデータ
    void QueueTransaction (CDWHCITransferStageData *pStageData);
    /// @brief 遅延を入れてトランザクションをキューに入れる
    /// @param pStageData トランザクションステージデータ
    void QueueDelayedTransaction (CDWHCITransferStageData *pStageData);
#endif
    /// @brief トランザクションを開始する
    /// @param pStageData トランザクションステージデータ
    void StartTransaction (CDWHCITransferStageData *pStageData);
    /// @brief チャネルを開始する
    /// @param pStageData トランザクションステージデータ
    void StartChannel (CDWHCITransferStageData *pStageData);
    /// @brief チャネル割り込みハンドラ
    /// @param nChannel チャネル番号
    void ChannelInterruptHandler (unsigned nChannel);
#ifdef USE_USB_SOF_INTR
    /// @brief SOF割り込みハンドラ
    void SOFInterruptHandler (void);
#endif
    /// @brief 割り込みハンドラ
    void InterruptHandler (void);
    /// @brief 割り込みスタブ
    /// @param pParam パラメタ（dwhciデバイスへのポインタ）
    static void InterruptStub (void *pParam);

#ifdef USE_USB_FIQ
    void InterruptHandler2 (void);
    static void InterruptStub2 (void *pParam);
#endif

#ifndef USE_USB_SOF_INTR
    void TimerHandler (CDWHCITransferStageData *pStageData);
    static void TimerStub (TKernelTimerHandle hTimer, void *pParam, void *pContext);
#endif
    /// @brief チャネルを割り当てる
    /// @return チャネル番号
    unsigned AllocateChannel (void);
    /// @brief チェネルを開放する
    /// @param nChannel チャネル番号
    void FreeChannel (unsigned nChannel);
    /// @brief waitblockを割り当てる
    /// @return waitblock
    unsigned AllocateWaitBlock (void);
    /// @brief waitblockを開放する
    /// @param nWaitBlock waitblock
    void FreeWaitBlock (unsigned nWaitBlock);

    /**
     * @brief 指定のビットが立つのを待つ
     * @param pRegister 対象レジスタ
     * @param nMask 対象ビット
     * @param bWaitUntilSet 待機ビット
     * @param nMsTimeout タイムアウト
     * @return ビットが立ったらTRUE, タイムアウトになったらFALSE
     */
    boolean WaitForBit (CDWHCIRegister *pRegister,
                u32            nMask,
                boolean        bWaitUntilSet,
                unsigned       nMsTimeout);

    void LogTransactionFailed (u32 nStatus);

#ifndef NDEBUG
    /// @brief レジスタ値をダンプ
    /// @param pName レジスタ名
    /// @param nAddress レジスタアドレス
    void DumpRegister (const char *pName, u32 nAddress);
    /// @brief ステータスをダンプ
    /// @param nChannel チャネル番号
    void DumpStatus (unsigned nChannel = 0);
#endif

private:
    CInterruptSystem *m_pInterruptSystem;       ///< 割り込みシステム
    CTimer *m_pTimer;                           ///< タイマー

    unsigned m_nChannels;                       ///< チャネル数
    volatile unsigned m_nChannelAllocated;      ///< 割り当て済みチャネル数: 1ビット1チャネル
    CSpinLock m_ChannelSpinLock;                ///< スピンロック: チャネルを保護

#ifdef USE_USB_SOF_INTR
    CDWHCITransactionQueue m_TransactionQueue;  ///< トランザクションキュー
#endif

    CDWHCITransferStageData *m_pStageData[DWHCI_MAX_CHANNELS];  ///< 転送ステートデータ

    CSpinLock m_IntMaskSpinLock;                ///< スピンロック: 割り込みマスクを保護

    volatile boolean m_bWaiting[DWHCI_WAIT_BLOCKS]; ///< 待機中
    volatile unsigned m_nWaitBlockAllocated;    ///< 割り当て済みウェイトブロック: 1ビット1wait block
    CSpinLock m_WaitBlockSpinLock;              ///< スピンロック: wait blockを保護

    CDWHCIRootPort m_RootPort;                  ///< ルートポート
    volatile boolean m_bRootPortEnabled;        ///< ルートポートが有効か

#ifdef USE_USB_FIQ
    volatile int m_nPortStatusChanged;          ///< ポートステータスが更新されたか
    CDWHCICompletionQueue m_CompletionQueue;    ///< 完了キュー
    CMPHIDevice m_MPHI;                         ///< MPHIデイバイス
#endif

    volatile boolean m_bShutdown;               ///< USBドライバはshutdownするか
};

/** @} */

#endif
