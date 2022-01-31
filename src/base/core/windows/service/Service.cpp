//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.

  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.

  For other usage or business cooperation, please contact admin@iMonitorSDK.com

--*/
//******************************************************************************
#include "stdafx.h"
#include "Service.h"
//******************************************************************************
cxService::cxService(SC_HANDLE SCMHandle, LPCTSTR Name, DWORD Access)
{
	Open(SCMHandle, Name, Access);
}
//******************************************************************************
HRESULT cxService::Open(SC_HANDLE SCMHandle, LPCTSTR Name, DWORD Access)
{
	Attach(::OpenService(SCMHandle, Name, Access));

	if (!operator bool())
		return HResultFromLastError();

	return S_OK;
}
//******************************************************************************
HRESULT cxService::Start(DWORD dwNumServiceArgs, LPCTSTR* lpServiceArgVectors)
{
	DCHECK(m_Handle != NULL);

	BOOL ret = StartService(m_Handle, dwNumServiceArgs, lpServiceArgVectors);

	return ret ? S_OK : HResultFromLastError();
}
//******************************************************************************
HRESULT cxService::Stop(void)
{
	return Control(SERVICE_CONTROL_STOP);
}
//******************************************************************************
HRESULT cxService::Delete(void)
{
	DCHECK(m_Handle != NULL);

	BOOL ret = DeleteService(m_Handle);

	return ret ? S_OK : HResultFromLastError();
}
//******************************************************************************
HRESULT cxService::Control(DWORD dwControl, LPSERVICE_STATUS lpServiceStatus)
{
	DCHECK(m_Handle != NULL);

	SERVICE_STATUS status = { 0 };

	if (!lpServiceStatus)
		lpServiceStatus = &status;

	BOOL ret = ControlService(m_Handle, dwControl, lpServiceStatus);

	return ret ? S_OK : HResultFromLastError();
}
//******************************************************************************
HRESULT cxService::SetConfigEx(DWORD dwInfoLevel, PVOID lpInfo)
{
	if (!ChangeServiceConfig2(m_Handle, dwInfoLevel, lpInfo))
		return HResultFromLastError();

	return S_OK;
}
//******************************************************************************
HRESULT cxService::WaitAndTerminate(ULONG msTimeout)
{
	SERVICE_STATUS_PROCESS status = {};
	QueryStatusProcess(&status);

	if (status.dwProcessId == 0)
		return S_OK;

	HANDLE process = OpenProcess(PROCESS_TERMINATE, FALSE, status.dwProcessId);

	if (!process)
		return E_FAIL;

	if (WAIT_TIMEOUT == WaitForSingleObject(process, msTimeout)) {
		TerminateProcess(process, ERROR_TIMEOUT);
	}

	CloseHandle(process);

	return S_OK;
}
//******************************************************************************
HRESULT cxService::QueryConfig(
	LPQUERY_SERVICE_CONFIG lpServiceConfig,
	DWORD cbBufSize,
	LPDWORD pcbBytesNeeded)
{
	DCHECK(m_Handle != NULL);

	BOOL ret = QueryServiceConfig(
		m_Handle,
		lpServiceConfig,
		cbBufSize,
		pcbBytesNeeded);

	return ret ? S_OK : HResultFromLastError();
}
//******************************************************************************
HRESULT cxService::QueryConfigEx(
	DWORD dwInfoLevel,
	LPBYTE lpServiceConfig,
	DWORD cbBufSize,
	LPDWORD pcbBytesNeeded)
{
	DCHECK(m_Handle != NULL);

	BOOL ret = QueryServiceConfig2(
		m_Handle,
		dwInfoLevel,
		lpServiceConfig,
		cbBufSize,
		pcbBytesNeeded);

	return ret ? S_OK : HResultFromLastError();
}
//******************************************************************************
HRESULT cxService::QueryStatus(LPSERVICE_STATUS lpStatus)
{
	return QueryServiceStatus(m_Handle, lpStatus) ? S_OK : HResultFromLastError();
}
//******************************************************************************
HRESULT cxService::QueryStatusProcess(LPSERVICE_STATUS_PROCESS lpStatus)
{
	ULONG len = 0;

	if (!QueryServiceStatusEx(m_Handle, SC_STATUS_PROCESS_INFO, (PBYTE)lpStatus, sizeof(SERVICE_STATUS_PROCESS), &len))
		return HResultFromLastError();

	return S_OK;
}
//******************************************************************************
SERVICE_STATUS cxService::GetStatus(void)
{
	SERVICE_STATUS status = {};
	QueryStatus(&status);
	return status;
}
//******************************************************************************
