//
// dwhcixferstagedata.h
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
#ifndef _circle_usb_dwhcixferstagedata_h
#define _circle_usb_dwhcixferstagedata_h

#include <circle/usb/usb.h>
#include <circle/usb/usbrequest.h>
#include <circle/usb/usbdevice.h>
#include <circle/usb/usbendpoint.h>
#include <circle/usb/dwhciframescheduler.h>
#include <circle/classallocator.h>
#include <circle/synchronize.h>
#include <circle/types.h>

/**
 * @class CDWHCITransferStageData
 * @brief 転送ステージデータを表すクラス
 */
class CDWHCITransferStageData
{
public:
    /**
     * コンストラクタ
     * @param nChannel チャネル
     * @param pURB リクエスト
     * @param bIn INリクエストか
     * @param bStatusStage ステータスステージか
     * @param nTimeoutMs タイムアウト時間
     */
    CDWHCITransferStageData (unsigned nChannel, CUSBRequest *pURB, boolean bIn,
                 boolean bStatusStage, unsigned nTimeoutMs);
    //! デストラクタ
    ~CDWHCITransferStageData (void);

    /**
     * チャネル番号を再割り当て
     * @param nChannel チャネル
     */
    void SetChannelNumber (unsigned nChannel);

    // ステージを変更する

    /**
     * トランザクション完了
     * @param nStatus ステータス
     * @param nPacketsLeft 残りのパケット数
     * @param nBytesLeft 残りのバイト数
     */
    void TransactionComplete (u32 nStatus, u32 nPacketsLeft, u32 nBytesLeft);
    /**
     * スプリット完了をセット
     * @param bComplete 完了
     */
    void SetSplitComplete (boolean bComplete);

    // setter, getter

    //! ステータスのset
    /*!
      \param nState ステータス値
    */
    void SetState (unsigned nState);
    //! ステータスのget
    /*!
      \return ステータス値
    */
    unsigned GetState (void) const;
    //! サブステータスのset
    void SetSubState (unsigned nSubState);
    //! サブステータスのget
    unsigned GetSubState (void) const;
    //! スプリットサイクル開始
    boolean BeginSplitCycle (void);

    // トランザクションパラメタのgetter

    //! チャネル番号をget
    unsigned GetChannelNumber (void) const;
    //! デバイスアドレスをget
    u8 GetDeviceAddress (void) const;
    //! 周期か
    boolean IsPeriodic (void) const;
    //! エンドポイントタイプをget
    u8 GetEndpointType (void) const;
    //! エンドポイント番号をget
    u8 GetEndpointNumber (void) const;
    //! 最大パケットサイズをget
    u32 GetMaxPacketSize (void) const;
    //! スピードをget
    TUSBSpeed GetSpeed (void) const;
    //! PIDをget
    u8 GetPID (void) const;
    //! 方向は入力か
    boolean IsDirectionIn (void) const;
    //! ステータスステージか
    boolean IsStatusStage (void) const;
    //! DMAアドレスをget
    u32 GetDMAAddress (void) const;
    //! バイト2転送をget
    u32 GetBytesToTransfer (void) const;
    //! パケット2転送をget
    u32 GetPacketsToTransfer (void) const;
    //! スプリット転送か
    boolean IsSplit (void) const;
    //! スプリットは完了か
    boolean IsSplitComplete (void) const;
    //! ハブアドレスをget
    u8 GetHubAddress (void) const;
    //! ハブポートアドレスをget
    u8 GetHubPortAddress (void) const;
    //! スプリット位置をget
    u8 GetSplitPosition (void) const;
    //! ステータスマスクをget
    u32 GetStatusMask (void) const;

    // トランザクション語に状態をチェックする

    //! トランザクションステータスをget
    u32 GetTransactionStatus (void) const;
    //! USBエラーをget
    TUSBError GetUSBError (void) const;
    //! ステージは完了したか
    boolean IsStageComplete (void) const;
    //! 転送サイズをget
    u32 GetResultLen (void) const;
    //! タイムアウトか
    boolean IsTimeout (void) const;
    //! リトライOKか
    boolean IsRetryOK (void) const;
    //! USBリクエストをget
    CUSBRequest *GetURB (void) const;
    //! デバイスをget
    CUSBDevice *GetDevice (void) const;
    //! フレームスケジューラをget
    CDWHCIFrameScheduler *GetFrameScheduler (void) const;
    //! デバッグダンプ
    void DebugStdata(void);

private:
    unsigned        m_nChannel;                 ///< チャネル
    CUSBRequest    *m_pURB;                     ///< リクエスト
    boolean         m_bIn;                      ///< 方向（INか）
    boolean         m_bStatusStage;             ///< ステージステータス
    unsigned        m_nTimeoutHZ;               ///< タイムアウト

    boolean         m_bSplitTransaction;        ///< 分割トランザクションか
    boolean         m_bSplitComplete;           ///< 分割完了か

    CUSBDevice     *m_pDevice;                  ///< デバイス
    CUSBEndpoint   *m_pEndpoint;                ///< エンドポイント
    TUSBSpeed       m_Speed;                    ///< 速度
    u32             m_nMaxPacketSize;           ///< 最大パケットサイズ

    u32             m_nTransferSize;            ///< 転送サイズ
    unsigned        m_nPackets;                 ///< パケット数
    u32             m_nBytesPerTransaction;     ///< トランザクションあたりのバイト数
    unsigned        m_nPacketsPerTransaction;   ///< トランザクションあたりのパケット数
    u32             m_nTotalBytesTransfered;    ///< 総転送バイト

    unsigned        m_nState;                   ///< 状態
    unsigned        m_nSubState;                ///< 副状態
    u32             m_nTransactionStatus;       ///< トランザクション状態
    unsigned        m_nErrorCount;              ///< エラー数

    DMA_BUFFER (u32, m_TempBuffer, 1);          //< 一時バッファの配列
    void           *m_pBufferPointer;           ///< バッファへのポインタ

    unsigned        m_nStartTicksHZ;            ///< スタート時

    CDWHCIFrameScheduler    *m_pFrameScheduler; ///< フレームスケジューラ

    DECLARE_CLASS_ALLOCATOR
};

#endif
