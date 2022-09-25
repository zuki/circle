//
// ntpclient.h
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
#ifndef _circle_net_ntpclient_h
#define _circle_net_ntpclient_h

#include <circle/net/netsubsystem.h>
#include <circle/net/ipaddress.h>

/// @brief NTPクライアントクラス
class CNTPClient
{
public:
    /// @brief コンストラクタ
    /// @param pNetSubSystem ネットワークサブシステムオブジェクトへのポインタ
    CNTPClient (CNetSubSystem *pNetSubSystem);
    /// @brief デストラクタ
    ~CNTPClient (void);

    /// @brief NTPサーバから現在時刻を取得する
    /// @param rServerIP NTPサーバのIPアドレス
    /// @return 1970-01-01 00:00:00 UTC以来の秒数、エラーの場合は0
    unsigned GetTime (CIPAddress &rServerIP);

private:
    /// @brief ネットワークサブシステムオブジェクト
    CNetSubSystem *m_pNetSubSystem;
};

#endif
