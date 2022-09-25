//
// usbconfigparser.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014  R. Stange <rsta2@o2online.de>
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
#ifndef _usbconfigparser_h
#define _usbconfigparser_h

#include <circle/usb/usb.h>
#include <circle/types.h>

/// @brief コンフィグレーションパーサ
class CUSBConfigurationParser
{
public:
    /// @brief コンストラクタ
    /// @param pBuffer データバッファ
    /// @param nBufLen バッファ長
    CUSBConfigurationParser (const void *pBuffer, unsigned nBufLen);
    /// @brief コピーコンストラクタ
    /// @param pParser コンフィグレーションパーサオブジェクトへのポインタ
    CUSBConfigurationParser (CUSBConfigurationParser *pParser);
    /// @brief デストラクタ
    ~CUSBConfigurationParser (void);
    /// @brief データはディスクリプタとして正しいか
    /// @return 正しければTRUE
    boolean IsValid (void) const;

    /// @brief 指定のタイプのディスクリプタを取得する
    /// @param ucType ディスクリプタタイプ
    /// @return ディスクリプタへのポインタ。見つからなかった場合は0
    const TUSBDescriptor *GetDescriptor (u8 ucType);
    /// @brief 現在のディスクリプタ
    /// @return ディスクリプタへのポインタ
    const TUSBDescriptor *GetCurrentDescriptor (void);
    /// @brief エラー出力
    /// @param pSource エラー元
    void Error (const char *pSource) const;

private:
    /// @brief ディスクリプタの入ったバッファ
    const TUSBDescriptor   *m_pBuffer;
    /// @brief ディスクリプタの合計サイズ
    unsigned                m_nBufLen;
    /// @brief ディスクリプタデータとして正しいか
    boolean                 m_bValid;
    /// @brief 最後のディスクリプタのポインタ
    const TUSBDescriptor   *m_pEndPosition;
    /// @brief 次のディスクリプタのポインタ
    const TUSBDescriptor   *m_pNextPosition;
    /// @brief 現在のディスクリプタのポインタ
    const TUSBDescriptor   *m_pCurrentDescriptor;
    /// @brief エラーが発生したディスクリプタのポインタ
    const TUSBDescriptor   *m_pErrorPosition;
};

#endif
