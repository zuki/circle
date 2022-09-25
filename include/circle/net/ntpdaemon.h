//
// ntpdaemon.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2020  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_net_ntpdaemon_h
#define _circle_net_ntpdaemon_h

#include <circle/sched/task.h>
#include <circle/net/netsubsystem.h>
#include <circle/string.h>

/// @brief NTDデーモンクラス
class CNTPDaemon : public CTask
{
public:
    /// @brief コンストラクタ
    /// @param pNTPServer NTPサーバのホスト名
    /// @param pNetSubSystem ネットサブシステムオブジェクトへのポインタ
    CNTPDaemon (const char  *pNTPServer,
            CNetSubSystem   *pNetSubSystem);
    /// @brief デストラクタ
    ~CNTPDaemon (void);
    /// @brief デーモン実行
    void Run (void);

private:
    /// @brief NTPから時刻を取得して現在痔を更新する
    /// @return 次の更新までの秒数
    unsigned UpdateTime (void);

private:
    /// @brief NTPサーバのホスト名
    CString         m_NTPServer;
    /// @brief ネットサブシステム
    CNetSubSystem  *m_pNetSubSystem;
};

#endif
