//
// usbrequest.h
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
#ifndef _circle_usb_usbrequest_h
#define _circle_usb_usbrequest_h

#include <circle/usb/usb.h>
#include <circle/usb/usbendpoint.h>
#include <circle/classallocator.h>
#include <circle/types.h>

class CUSBRequest;

typedef void TURBCompletionRoutine (CUSBRequest *pURB, void *pParam, void *pContext);

/**
 * @class CUSBRequest
 * @brief USBリクエストを表すクラス
 */
class CUSBRequest
{
public:
    /**
     * コンストラクタ
     * @param pEndpoint エンドポイントへのポインタ
     * @param pBuffer   バッファポインタ
     * @param nBufLen   バッファ長
     * @param pSetupData    セットアップデータ
     */
    CUSBRequest (CUSBEndpoint *pEndpoint, void *pBuffer, u32 nBufLen, TSetupData *pSetupData = 0);
    /**
     * デストラクタ
     */
    ~CUSBRequest (void);

    /**
     * エンドポイントを取得
     * @return エンドポイントへのポインタ
     */
    CUSBEndpoint *GetEndpoint (void) const;
    /**
     * ステータスをセット
     * @param bStatus ステータス
     */
    void SetStatus (int bStatus);
    /**
     * 結果の長さをセット
     * @param nLength 実際の長さ
     */
    void SetResultLen (u32 nLength);
    /**
     * エラーをセット
     * @param Error エラー
     */
    void SetUSBError (TUSBError Error);

    /**
     * ステータスを取得
     * @return ステータス
     */
    int GetStatus (void) const;
    /**
     * 結果の長さを取得
     * @return 結果の長さ
     */
    u32 GetResultLength (void) const;
    /**
     * エラーを取得
     * @return エラー
     */
    TUSBError GetUSBError (void) const;

    /**
     * セットアップデータを取得
     * @return セットアップデータ
     */
    TSetupData *GetSetupData (void);
    /**
     * バッファを取得
     * @return バッファ
     */
    void *GetBuffer (void);
    /**
     * バッファ長を取得
     * @return バッファ長
     */
    u32 GetBufLen (void) const;

    /**
     * 完了時CBをセット
     * @param pRoutine コールバック関数
     * @param pParam コールバック引数
     * @param pContext 実行コンテキスト
     */
    void SetCompletionRoutine (TURBCompletionRoutine *pRoutine, void *pParam, void *pContext);
    /**
     * 完了時CBを呼び出し
     */
    void CallCompletionRoutine (void);

    /**
     * NAK時完了フラグをセット
     * リクエストがすぐに提供されなかった場合、リトライをしない（バルク入力のみ）
     */
    void SetCompleteOnNAK (void);
    /**
     * NAK時完了フラグを取得
     * @return NAK時に完了するか
     */
    boolean IsCompleteOnNAK (void) const;

private:
    CUSBEndpoint   *m_pEndpoint;                    /**< エンドポイント */

    TSetupData     *m_pSetupData;                   /**< セットアップデータ */
    void           *m_pBuffer;                      /**< バッファ */
    u32             m_nBufLen;                      /**< バッファ長 */

    int             m_bStatus;                      /**< ステータス */
    u32             m_nResultLen;                   /**< 実際の長さ */
    TUSBError       m_USBError;                     /**< エラー */

    TURBCompletionRoutine *m_pCompletionRoutine;    /**< 完了時cbルーチン */
    void *m_pCompletionParam;                       /**< cbルーチン引数 */
    void *m_pCompletionContext;                     /**< 完了時コンテキスト */

    boolean m_bCompleteOnNAK;                       /**<  */

    DECLARE_CLASS_ALLOCATOR
};

#endif
