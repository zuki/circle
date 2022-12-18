//
// ptrarray.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_ptrarray_h
#define _circle_ptrarray_h

/// @brief ポインタを格納する動的配列クラス
class CPtrArray
{
public:
    CPtrArray (unsigned nInitialSize = 100, unsigned nSizeIncrement = 100);
    ~CPtrArray (void);

    /// @brief 配列の要素数を取得
    unsigned GetCount (void) const;

    /// @brief &[]オペレータ: 指定したインデックスの要素を取得
    /// @param nIndex インデックス
    /// @return 指定したインデックスに格納されているポインタ
    void *&operator[] (unsigned nIndex);

    /// @brief []オペレータ: 指定したインデックスの要素を取得
    /// @param nIndex インデックス
    /// @return 指定したインデックスに格納されているポインタ
    void *operator[] (unsigned  nIndex) const;

    /// @brief 配列の末尾に要素を追加する
    /// @param pPtr 要素へのポインタ
    /// @return 要素数
    unsigned Append (void *pPtr);

    /// @brief 配列の最後の要素を削除する
    void RemoveLast (void);

private:
    unsigned  m_nReservedSize;      ///< 確保済み要素数
    unsigned  m_nSizeIncrement;     ///< 拡張増分数
    unsigned  m_nUsedCount;         ///< 使用済み要素数
    void    **m_ppArray;            ///< この配列のポインタ
};

#endif
