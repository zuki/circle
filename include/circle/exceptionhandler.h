//
// exceptionhandler.h
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
#ifndef _exceptionhandler_h
#define _exceptionhandler_h

#include <circle/exception.h>
#include <circle/exceptionstub.h>

/// @brief 例外ハンドラクラス
class CExceptionHandler
{
public:
    /// @brief コンストラクタ
    CExceptionHandler (void);
    /// @brief ディスクリプタ
    ~CExceptionHandler (void);
    /// @brief 例外を投げる
    /// @param nException 例外
    void Throw (unsigned nException);
    /// @brief エラーフレームを指定して例外を投げる
    /// @param nException れ以外
    /// @param pFrame エラーフレーム
    void Throw (unsigned nException, TAbortFrame *pFrame);
    /// @brief 例外ハンドラを取得
    /// @return 例外ハンドラ
    static CExceptionHandler *Get (void);

private:
    /// @brief 例外を表す文字列配列
    static const char *s_pExceptionName[];
    /// @brief この唯一のオブジェクト
    static CExceptionHandler *s_pThis;
};

#endif
