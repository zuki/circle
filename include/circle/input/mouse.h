//
// mouse.h
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
#ifndef _circle_input_mouse_h
#define _circle_input_mouse_h

#include <circle/device.h>
#include <circle/input/mousebehaviour.h>
#include <circle/numberpool.h>
#include <circle/types.h>

#define MOUSE_DISPLACEMENT_MIN    -127
#define MOUSE_DISPLACEMENT_MAX    127

typedef void TMouseStatusHandler (unsigned nButtons, int nDisplacementX, int nDisplacementY, int nWheelMove);

/**
 * @class CMouseDevice
 * @brief 汎用マウスインタフェースデバイス ("mouse1")
 */
class CMouseDevice : public CDevice    /// Generic mouse interface device ("mouse1")
{
public:
    /// \brief マウスデバイスインタフェースのコンストラクタ
    /// \param nButtons ボタン数
    /// \param bHasWheel ホイールの有無
    CMouseDevice (unsigned nButtons, boolean bHasWheel = FALSE);
    ~CMouseDevice (void);

    /// \brief マウスデバイスをクックモードでセットアップする
    /// \param nScreenWidth  スクリーンの幅（ピクセル単位）
    /// \param nScreenHeight スクリーンの高さ（ピクセル単位）
    /// \return 失敗したらFALSE
    boolean Setup (unsigned nScreenWidth, unsigned nScreenHeight);

    /// \brief クックモードのイベントハンドラを登録する
    /// \param pEventHandler イベントハンドラへのポインタ（ mousebehaviour.hを参照）
    void RegisterEventHandler (TMouseEventHandler *pEventHandler);

    /// \brief 指定した位置にマウスカーソルをクックモードでセットする
    /// \param nPosX 位置のX-座標（ピクセル単位、0は左端）
    /// \param nPosY 位置のY-座標（ピクセル単位、0は上
    /// \return 失敗したらFALSE
    boolean SetCursor (unsigned nPosX, unsigned nPosY);
    /// \brief クックモードのマウスカーソルのオン/オフ切り替え
    /// \param bShow TRUEはマウスカーソルを表示する
    /// \return 以前のステート
    boolean ShowCursor (boolean bShow);

    /// \brief この関数をTASK_LEVELから頻繁に呼び出す（クックモードのみ）
    void UpdateCursor (void);

    /// \brief rawモードのマウスステートハンドラを登録する
    /// \param pStatusHandler マウスステートハンドラへのポインタ
    void RegisterStatusHandler (TMouseStatusHandler *pStatusHandler);

    /// \return サポートされているボタンの数
    unsigned GetButtonCount (void) const;

    /// \return マウスホイールをサポートしているか?
    boolean HasWheel (void) const;

public:
    /// \warning このハンドラをアプリケーションから呼び出さないこと!
    void ReportHandler (unsigned nButtons, int nDisplacementX, int nDisplacementY, int nWheelMove);

private:
    CMouseBehaviour m_Behaviour;            //< マウスビヘイビア

    TMouseStatusHandler *m_pStatusHandler;  //< マウスステータスハンドラ

    unsigned m_nDeviceNumber;               //< デバイス番号
    static CNumberPool s_DeviceNumberPool;  //< デバイス番号プール

    unsigned m_nButtons;                    //< ボタン数
    boolean m_bHasWheel;                    //< ホイールの有無
};

#endif
