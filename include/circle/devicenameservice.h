//
// devicenameservice.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2018  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_devicenameservice_h
#define _circle_devicenameservice_h

#include <circle/device.h>
#include <circle/spinlock.h>
#include <circle/types.h>

struct TDeviceInfo
{
    TDeviceInfo    *pNext;
    char           *pName;
    CDevice        *pDevice;
    boolean         bBlockDevice;
};

/// @brief デバイス名前サービス. \n
/// デバイスを名前で登録し、後でこの名前でデバイスを検索可能にする
class CDeviceNameService
{
public:
    CDeviceNameService (void);
    ~CDeviceNameService (void);

    /// デバイスを追加する
    /// \param pName        デバイス名文字列
    /// \param pDevice      デバイスオブジェクトへのポインタ
    /// \param bBlockDevice ブロックデバイスの場合はTRUE、それ以外はキャラクタデバイス
    void AddDevice (const char *pName, CDevice *pDevice, boolean bBlockDevice);

    /// デバイスを追加する
    /// \param pPrefix      デバイス名のプリフィックス文字列
    /// \param nIndex       デバイス名のインデックス
    /// \param pDevice      デバイスオブジェクトへのポインタ
    /// \param bBlockDevice ブロックデバイスの場合はTRUE、それ以外はキャラクタデバイス
    void AddDevice (const char *pPrefix, unsigned nIndex, CDevice *pDevice, boolean bBlockDevice);

    /// デバイスを削除する
    /// \param pName        デバイス名文字列
    /// \param bBlockDevice ブロックデバイスの場合はTRUE、それ以外はキャラクタデバイス
    void RemoveDevice (const char *pName, boolean bBlockDevice);

    /// デバイスを削除する
    /// \param pPrefix      デバイス名のプリフィックス文字列
    /// \param nIndex       デバイス名のインデックス
    /// \param bBlockDevice ブロックデバイスの場合はTRUE、それ以外はキャラクタデバイス
    void RemoveDevice (const char *pPrefix, unsigned nIndex, boolean bBlockDevice);

    /// デバイスをデバイス名で取得する
    /// \param pName        デバイス名文字列
    /// \param bBlockDevice ブロックデバイスの場合はTRUE、それ以外はキャラクタデバイス
    /// \return デバイスオブジェクトへのポインタ、見つからない場合は0
    CDevice *GetDevice (const char *pName, boolean bBlockDevice);

    /// デバイスをデバイス名プリフィックスとインデックスで取得する
    /// \param pPrefix      デバイス名のプリフィックス文字列
    /// \param nIndex       デバイス名のインデックス
    /// \param bBlockDevice ブロックデバイスの場合はTRUE、それ以外はキャラクタデバイス
    /// \return デバイスオブジェクトへのポインタ、見つからない場合は0
    CDevice *GetDevice (const char *pPrefix, unsigned nIndex, boolean bBlockDevice);

    /// \brief デバイスリストを生成する
    /// \param pTarget 出力に使用するデバイス
    void ListDevices (CDevice *pTarget);

    /// \return システムにただ一つのCDeviceNameServiceインスタンス
    static CDeviceNameService *Get (void);

private:
    TDeviceInfo *m_pList;       //< デバイスリスト

    CSpinLock m_SpinLock;       //< スピンロック

    static CDeviceNameService *s_This;  // CDeviceNameServiceインスタンス
};

#endif
