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
#include "ServiceImplement.h"
//******************************************************************************
static cxServiceImplement* g_lpService = nullptr;
//******************************************************************************
void WINAPI cxServiceImplement::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	struct stub
	{
		static DWORD WINAPI Handler(
			DWORD dwControl,
			DWORD dwEventType,
			LPVOID lpEventData,
			LPVOID lpContext)
		{
			return g_lpService->ServiceHandler(
				dwControl,
				dwEventType,
				lpEventData);
		}
	};

	DCHECK(g_lpService != nullptr);
	DCHECK(g_lpService->m_ServiceStatusHandle == nullptr);

	g_lpService->m_ServiceStatusHandle = RegisterServiceCtrlHandlerEx(
		g_lpService->m_ServiceName,
		stub::Handler,
		nullptr);

	if (!g_lpService->m_ServiceStatusHandle) {
		return;
	}

	if (!g_lpService->OnStart(dwArgc, lpszArgv)) {
		g_lpService->ChangeStatus(SERVICE_STOPPED);
		return;
	};

	g_lpService->ChangeStatus(SERVICE_RUNNING);
}
//******************************************************************************
cxServiceImplement::cxServiceImplement()
{
	g_lpService = this;

	m_ServiceStatus.dwServiceType = SERVICE_WIN32;
	m_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	m_ServiceStatus.dwControlsAccepted = ServiceDefaultControls;
	m_ServiceStatus.dwWin32ExitCode = 0;
	m_ServiceStatus.dwServiceSpecificExitCode = 0;
	m_ServiceStatus.dwCheckPoint = 0;
	m_ServiceStatus.dwWaitHint = 0;

	m_ServiceStatusHandle = nullptr;
}
//******************************************************************************
cxServiceImplement::~cxServiceImplement()
{
	g_lpService = nullptr;
}
//******************************************************************************
int cxServiceImplement::WinMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	return ControlService(dwArgc, lpszArgv);
}
//******************************************************************************
DWORD cxServiceImplement::ServiceHandler(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData)
{
	switch (dwControl) {
	case SERVICE_CONTROL_STOP:
		OnStop();
		ChangeStatus(SERVICE_STOPPED);
		break;

	case SERVICE_CONTROL_PAUSE:
		ChangeStatus(SERVICE_PAUSED);
		break;

	case SERVICE_CONTROL_CONTINUE:
		ChangeStatus(SERVICE_RUNNING);
		break;

	case SERVICE_CONTROL_SHUTDOWN:
		OnStop();
		ChangeStatus(SERVICE_STOPPED);
		break;

	case SERVICE_CONTROL_SESSIONCHANGE: {
		DWORD dwSessionId = ((PWTSSESSION_NOTIFICATION)lpEventData)->dwSessionId;
		OnSessionEvent(dwEventType, dwSessionId);
	} break;

	case SERVICE_CONTROL_POWEREVENT:
		OnPowerEvent(dwEventType);
		break;

	default:
		return ERROR_CALL_NOT_IMPLEMENTED;
		break;
	}

	return NO_ERROR;
}
//******************************************************************************
bool cxServiceImplement::StartDispatcher()
{
	if (!g_lpService)
		return false;

	SERVICE_TABLE_ENTRY ServiceTableEntry[] = {
		{ m_ServiceName.GetBuffer(), ServiceMain },
		{ 0, 0 }
	};

	BOOL ret = StartServiceCtrlDispatcher(ServiceTableEntry);

	m_ServiceName.ReleaseBuffer();

	return TRUE == ret;
}
//******************************************************************************
bool cxServiceImplement::ChangeStatus(DWORD Status)
{
	m_ServiceStatus.dwCurrentState = Status;

	return TRUE == SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);
}
//******************************************************************************
bool cxServiceImplement::ControlService(DWORD dwArgc, LPTSTR* lpszArgv)
{
#define OnEvent(Function) \
	if (Function()) {     \
		return TRUE;      \
	} else {              \
		return FALSE;     \
	}

	if (1 == dwArgc)
		return StartDispatcher();

	if (2 == dwArgc) {
		if (0 == _tcsicmp(lpszArgv[1], _T("/install")))
			OnEvent(InstallService);

		if (0 == _tcsicmp(lpszArgv[1], _T("/uninstall")))
			OnEvent(RemoveService);

		if (0 == _tcsicmp(lpszArgv[1], _T("/start")))
			OnEvent(StartService);

		if (0 == _tcsicmp(lpszArgv[1], _T("/stop")))
			OnEvent(StopService);

		if (0 == _tcsicmp(lpszArgv[1], _T("/debug")))
			OnEvent(DebugService);
	}

	if (3 == dwArgc) {
		if (0 == _tcsicmp(lpszArgv[1], _T("/install")) && 0 == _tcsicmp(lpszArgv[2], _T("/start")))
			OnEvent(InstallAndStart);
	}

	return FALSE;
}
//******************************************************************************
bool cxServiceImplement::InstallService()
{
	DCHECK(!m_ServiceName.IsEmpty());
	DCHECK(!m_DisplayName.IsEmpty());

	TCHAR lpPath[MAX_PATH] = {};
	TCHAR lpPathFixed[MAX_PATH] = {};
	GetModuleFileName(nullptr, lpPath, MAX_PATH);
	PathCanonicalize(lpPathFixed, lpPath);

	HRESULT hr = g_ServiceInstaller->InstallService(m_ServiceName, m_DisplayName, lpPathFixed);

	if (hr != S_OK)
		return false;

	if (m_Description) {
		SERVICE_DESCRIPTION Description;
		Description.lpDescription = m_Description.GetBuffer();

		g_ServiceInstaller->SetConfig(
			m_ServiceName,
			SERVICE_CONFIG_DESCRIPTION,
			&Description);

		m_Description.ReleaseBuffer();
	}

	return true;
}
//******************************************************************************
bool cxServiceImplement::StartService()
{
	DCHECK(!m_ServiceName.IsEmpty());

	InstallService();

	return S_OK == g_ServiceInstaller->StartService(m_ServiceName);
}
//******************************************************************************
bool cxServiceImplement::StopService()
{
	DCHECK(!m_ServiceName.IsEmpty());

	return S_OK == g_ServiceInstaller->StopService(m_ServiceName);
}
//******************************************************************************
bool cxServiceImplement::RemoveService()
{
	DCHECK(!m_ServiceName.IsEmpty());

	return S_OK == g_ServiceInstaller->RemoveService(m_ServiceName);
}
//******************************************************************************
bool cxServiceImplement::DebugService(void)
{
	OnStart(0, nullptr);

	system("pause");

	OnStop();

	return true;
}
//******************************************************************************
bool cxServiceImplement::InstallAndStart()
{
	return StartService();
}
//******************************************************************************
