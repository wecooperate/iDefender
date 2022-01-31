//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.

  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.

  For other usage or business cooperation, please contact admin@iMonitorSDK.com

--*/
//******************************************************************************
#include "stdafx.h"
#include "ServiceMain.h"
#include <atlsecurity.h>
//******************************************************************************
constexpr auto SERVICE_INSTANCE_NAME = _T("Global\\iDefender-0C4BF928BE85485DB65873B475099863");
//******************************************************************************
cxServcieMain::cxServcieMain(void)
{
	SetErrorMode(SEM_NOGPFAULTERRORBOX);

	m_ServiceName = _T("iDefender");
	m_DisplayName = _T("冰盾 - 终端主动防御系统服务");

	EnableDebugPrivilege();
}
//******************************************************************************
bool cxServcieMain::OnStart(DWORD dwArgc, LPTSTR* lpszArgv)
{
	HRESULT hr = m_Defender.Start();

	if (hr != S_OK) {
		SetLastError(hr);
		SPDLOG_ERROR("start error = {}", hr);
		return false;
	}

	m_InstanceMutex = CreateMutex(NULL, FALSE, SERVICE_INSTANCE_NAME);

	if (!m_InstanceMutex || GetLastError() == ERROR_ALREADY_EXISTS) {
		m_Defender.Stop();
		SPDLOG_ERROR("create mutex failed");
		return false;
	}

	g_Looper->Start(false);

	return true;
}
//******************************************************************************
void cxServcieMain::OnStop(void)
{
	m_Defender.Stop();

	g_Looper->Stop();

	m_InstanceMutex.Close();
}
//******************************************************************************
