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
#include "ServiceInstaller.h"
//******************************************************************************
bool cxServiceInstaller::IsServiceInstalled(LPCTSTR lpServiceName)
{
	cxServiceManager scm;

	cxService service(scm.OpenService(
		lpServiceName,
		SERVICE_QUERY_CONFIG));

	return service;
}
//******************************************************************************
HRESULT cxServiceInstaller::InstallService(
	LPCTSTR lpServiceName,
	LPCTSTR lpDisplayName,
	LPCTSTR lpPath)
{
	cxServiceManager scm;

	cxService service(scm.CreateService(
		lpServiceName,
		lpDisplayName,
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		lpPath));

	if (service)
		return S_OK;

	DWORD dwError = GetLastError();

	if (ERROR_SERVICE_EXISTS != dwError)
		return HResultFromLastError(dwError);

	service.Attach(scm.OpenService(lpServiceName));

	if (!service)
		return HResultFromLastError();

	ChangeServiceConfig(
		service,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		lpPath,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr);

	return S_OK;
}
//******************************************************************************
HRESULT cxServiceInstaller::StartService(LPCTSTR lpServiceName)
{
	cxServiceManager scm;

	cxService service(scm.OpenService(lpServiceName));

	if (!service)
		return HResultFromLastError();

	HRESULT hr = service.Start();

	if (hr != S_OK && hr != HRESULT_FROM_WIN32(ERROR_SERVICE_ALREADY_RUNNING))
		return hr;

	return S_OK;
}
//******************************************************************************
HRESULT cxServiceInstaller::StopService(LPCTSTR lpServiceName)
{
	cxServiceManager scm;

	cxService service(scm.OpenService(lpServiceName));

	if (!service) {
		if (ERROR_SERVICE_DOES_NOT_EXIST == GetLastError())
			return S_OK;

		return HResultFromLastError();
	}

	HRESULT hr = service.Stop();

	return hr;
}
//******************************************************************************
HRESULT cxServiceInstaller::RemoveService(LPCTSTR lpServiceName)
{
	cxServiceManager scm;

	cxService service(scm.OpenService(lpServiceName));

	if (!service) {
		if (ERROR_SERVICE_DOES_NOT_EXIST == GetLastError())
			return S_OK;

		return HResultFromLastError();
	}

	service.Stop();
	service.WaitAndTerminate(10000);

	return service.Delete();
}
//******************************************************************************
HRESULT cxServiceInstaller::SetConfig(LPCTSTR lpServiceName, DWORD dwType, PVOID lpInfo)
{
	cxServiceManager scm;

	cxService service(scm.OpenService(lpServiceName, SERVICE_CHANGE_CONFIG));

	if (!service)
		return HResultFromLastError();

	return service.SetConfigEx(dwType, lpInfo);
}
//******************************************************************************
