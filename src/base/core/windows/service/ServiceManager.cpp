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
#include "ServiceManager.h"
//******************************************************************************
cxServiceManager::cxServiceManager(DWORD Access)
{
	m_Handle = OpenSCManager(NULL, NULL, Access);
}
//******************************************************************************
SC_HANDLE cxServiceManager::OpenService(LPCTSTR lpServiceName, DWORD dwDesiredAccess)
{
	return ::OpenService(m_Handle, lpServiceName, dwDesiredAccess);
}
//******************************************************************************
SC_HANDLE cxServiceManager::CreateService(
	LPCTSTR lpServiceName,
	LPCTSTR lpDisplayName,
	DWORD dwDesiredAccess,
	DWORD dwServiceType,
	DWORD dwStartType,
	DWORD dwErrorControl,
	LPCTSTR lpPath,
	LPCTSTR lpLoadOrderGroup,
	LPCTSTR lpDependencies,
	LPCTSTR lpServiceStartName,
	LPCTSTR lpPassword)
{
	return ::CreateService(
		m_Handle,
		lpServiceName,
		lpDisplayName,
		dwDesiredAccess,
		dwServiceType,
		dwStartType,
		dwErrorControl,
		lpPath,
		lpLoadOrderGroup,
		NULL,
		lpDependencies,
		lpServiceStartName,
		lpPassword);
}
//******************************************************************************
