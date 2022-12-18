/** @addtogroup net_core
 *  @{
 */
//
// ipaddress.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2016  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_net_ipaddress_h
#define _circle_net_ipaddress_h

#include <circle/string.h>
#include <circle/types.h>

#define IP_ADDRESS_SIZE    4

/// @brief IPアドレスを表すクラス
class CIPAddress
{
public:
    /// @brief コンストラクタ
    CIPAddress (void);
    /// @brief コンストラクタ
    /// @param IPアドレス
    CIPAddress (u32 nAddress);
    /// @brief コンストラクタ
    /// @param IPアドレスを表すバイト列
    CIPAddress (const u8 *pAddress);
    /// @brief コピーコンストラクタ
    /// @param IPアドレスオブジェクトへのポインタ
    CIPAddress (const CIPAddress &rAddress);
    /// デストラクタ
    ~CIPAddress (void);
    /// @brief '=='演算子
    /// @param rAddress2 比較するアドレスオブジェクト
    /// @return 等しい場合はTRUE、そうでなければFALSE
    boolean operator== (const CIPAddress &rAddress2) const;
    /// @brief '!='演算子
    /// @param rAddress2 比較するアドレスオブジェクト
    /// @return 等しくない場合はTRUE、そうでなければFALSE
    boolean operator!= (const CIPAddress &rAddress2) const;
    /// @brief '=='演算子
    /// @param rAddress2 比較するアドレスを表すバイト列
    /// @return 等しい場合はTRUE、そうでなければFALSE
    boolean operator== (const u8 *pAddress2) const;
    /// @brief '!='演算子
    /// @param rAddress2 比較するアドレスを表すバイト列
    /// @return 等しくない場合はTRUE、そうでなければFALSE
    boolean operator!= (const u8 *pAddress2) const;
    /// @brief '=='演算子
    /// @param rAddress2 比較するアドレス
    /// @return 等しい場合はTRUE、そうでなければFALSE
    boolean operator== (u32 nAddress2) const;
    /// @brief '!='演算子
    /// @param rAddress2 比較するアドレス
    /// @return 等しくない場合はTRUE、そうでなければFALSE
    boolean operator!= (u32 nAddress2) const;
    /// @brief '='演算子
    /// @param rAddress2 比較するアドレス
    /// @return オブジェクト自身
    CIPAddress &operator= (u32 nAddress);
    /// @brief アドレスをセットする
    /// @param nAddress アドレス
    void Set (u32 nAddress);
    /// @brief アドレスをセットする
    /// @param nAddress アドレスを表すバイト列
    void Set (const u8 *pAddress);
    /// @brief アドレスをセットする
    /// @param nAddress アドレスオブジェクト
    void Set (const CIPAddress &rAddress);
    /// @brief ブロードキャストアドレスをセットする
    void SetBroadcast (void);
    /// @brief アドレスをu32で返す
    operator u32 (void) const;
    /// @brief アドレスをバイト列で返す
    /// @return アドレスを表すバイト列
    const u8 *Get (void) const;
    /// @brief アドレスをコピーする
    /// @param pBuffer コピー先のバッファ
    void CopyTo (u8 *pBuffer) const;
    /// @brief ヌルアドレスか
    /// @return ヌルアドレスならTRUE、そうでなければFALSE
    boolean IsNull (void) const;
    /// @brief ブロードキャストアドレスか
    /// @return ブロードキャストアドレスならTRUE、そうでなければFALSE
    boolean IsBroadcast (void) const;
    /// @brief IPアドレスの長さを取得する
    /// @return IPアドレスの長さ
    unsigned GetSize (void) const;
    /// @brief IPアドレスを表示用文字列に変換する
    /// @param pString IPアドレスを設定するCStringへのポインタ
    void Format (CString *pString) const;
    /// @brief 指定したアドレス（サブネットマスクを考慮して）このアドレスと同じネットワークのアドレスか
    /// @param rAddress2 比較するIPアドレス
    /// @param pNetMask サブネットマスク
    /// @return 同じネットワークにあればTRUE、そうでなければFALSE
    boolean OnSameNetwork (const CIPAddress &rAddress2, const u8 *pNetMask) const;

private:
#ifndef NDEBUG
    /// @brief 正しいアドレスか
    boolean m_bValid;
#endif
    /// @brief アドレス値
    u32 m_nAddress;
};

/** @} */
#endif
