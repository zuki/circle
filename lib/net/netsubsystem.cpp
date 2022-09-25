//
// netsubsystem.cpp
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
#include <circle/net/netsubsystem.h>
#include <circle/net/nettask.h>
#include <circle/net/dhcpclient.h>
#include <circle/sched/scheduler.h>
#include <assert.h>

CNetSubSystem *CNetSubSystem::s_pThis = 0;

CNetSubSystem::CNetSubSystem (const u8 *pIPAddress, const u8 *pNetMask, const u8 *pDefaultGateway,
                  const u8 *pDNSServer, const char *pHostname, TNetDeviceType DeviceType)
:   m_Hostname (pHostname != 0 ? pHostname : ""),
    m_NetDevLayer (&m_Config, DeviceType),
    m_LinkLayer (&m_Config, &m_NetDevLayer),
    m_NetworkLayer (&m_Config, &m_LinkLayer),
    m_TransportLayer (&m_Config, &m_NetworkLayer),
    m_bUseDHCP (pIPAddress == 0 ? TRUE : FALSE),
    m_pDHCPClient (0)
{
    assert (s_pThis == 0);
    s_pThis = this;
    // DHcPの使用の有無を設定
    m_Config.SetDHCP (m_bUseDHCP);
    // DHCPを使用しないはIPアドレス、サブネットマスク、デフォルトゲートウェイ、DNSサーバを設定
    if (!m_bUseDHCP)
    {
        m_Config.SetIPAddress (pIPAddress);
        m_Config.SetNetMask (pNetMask);

        if (pDefaultGateway != 0)
        {
            m_Config.SetDefaultGateway (pDefaultGateway);
        }

        if (pDNSServer != 0)
        {
            m_Config.SetDNSServer (pDNSServer);
        }
    }
}

CNetSubSystem::~CNetSubSystem (void)
{
    s_pThis = 0;
}

boolean CNetSubSystem::Initialize (boolean bWaitForActivate)
{
    m_bUseDHCP = m_Config.GetIPAddress ()->IsNull ();
    m_Config.SetDHCP (m_bUseDHCP);
    // 物理層の初期化
    if (!m_NetDevLayer.Initialize (bWaitForActivate))
    {
        return FALSE;
    }
    // リンク層の初期化
    if (!m_LinkLayer.Initialize ())
    {
        return FALSE;
    }
    // ネットワーク層の初期化
    if (!m_NetworkLayer.Initialize ())
    {
        return FALSE;
    }
    // リンク層にネットワーク層をアタッチ
    m_LinkLayer.AttachLayer (&m_NetworkLayer);
    // トランスポート層を初期化
    if (!m_TransportLayer.Initialize ())
    {
        return FALSE;
    }
    // ネットワークタスクを作成
    new CNetTask (this);
    // ネットワークの立ち上げ理を待たない場合はTRUEでリターン
    if (!bWaitForActivate)
    {
        return TRUE;
    }
    // DHCPを使用する場合はDHCPクライアントを取得してセット
    if (m_bUseDHCP)
    {
        assert (m_pDHCPClient == 0);
        m_pDHCPClient = new CDHCPClient (this, m_Hostname);
        assert (m_pDHCPClient != 0);
    }

    while (!IsRunning ())
    {
        CScheduler::Get ()->Yield ();
    }

    return TRUE;
}

void CNetSubSystem::Process (void)
{
    if (s_pThis == 0)
    {
        return;
    }

    if (   m_bUseDHCP
        && m_pDHCPClient == 0
        && m_NetDevLayer.IsRunning ())
    {
        m_pDHCPClient = new CDHCPClient (this, m_Hostname);
        assert (m_pDHCPClient != 0);
    }
    // 物理層の処理を行う
    m_NetDevLayer.Process ();
    // リンク層の処理を行う
    m_LinkLayer.Process ();
    // ネットワーク層の処理を行う
    m_NetworkLayer.Process ();
    // トランスポート層の処理を行う
    m_TransportLayer.Process ();
}

CNetConfig *CNetSubSystem::GetConfig (void)
{
    return &m_Config;
}

CNetDeviceLayer *CNetSubSystem::GetNetDeviceLayer (void)
{
    return &m_NetDevLayer;
}

CLinkLayer *CNetSubSystem::GetLinkLayer (void)
{
    return &m_LinkLayer;
}

CTransportLayer *CNetSubSystem::GetTransportLayer (void)
{
    return &m_TransportLayer;
}

boolean CNetSubSystem::IsRunning (void) const
{
    if (!m_NetDevLayer.IsRunning ())
    {
        return FALSE;
    }

    if (!m_bUseDHCP)
    {
        return TRUE;
    }

    if (m_pDHCPClient == 0)
    {
        return FALSE;
    }

    return m_pDHCPClient->IsBound ();
}

CNetSubSystem *CNetSubSystem::Get (void)
{
    assert (s_pThis != 0);
    return s_pThis;
}
