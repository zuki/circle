/** @addtogroup net_core
 *  @{
 */
//
// netqueue.h
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
#ifndef _circle_net_netqueue_h
#define _circle_net_netqueue_h

#include <circle/spinlock.h>
#include <circle/types.h>

struct TNetQueueEntry;

/// @brief netdevlayerの送受信キューのためのクラス
class CNetQueue
{
public:
    CNetQueue (void);
    ~CNetQueue (void);

    /// @brief キューは空か
    /// @return からの場合はTRUE
    boolean IsEmpty (void) const;

    /// @brief キューをフラッシュ（クリア）する
    void Flush (void);

    /// @brief エントリをエンキュー
    /// @param pBuffer エントリデータ
    /// @param nLength エントリデータ長
    /// @param pParam エントリパラメタ
    void Enqueue (const void *pBuffer, unsigned nLength, void *pParam = 0);

    /// @brief エントリをデキュー
    /// @param pBuffer デキューしたエントリを格納するバッファ
    /// @param ppParam デキューしたエントリのパラメタを格納
    /// @return デキューしたエントリのデータ長（キューが空の場合は0）
    unsigned Dequeue (void *pBuffer, void **ppParam = 0);

private:
    volatile TNetQueueEntry *m_pFirst;  ///< 先頭のエントリ
    volatile TNetQueueEntry *m_pLast;   ///< 最後のエントリ

    CSpinLock m_SpinLock;               ///< キューを保護するロック
};

/** @} */

#endif
