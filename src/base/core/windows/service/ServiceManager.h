//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __ServiceManager_H__
#define __ServiceManager_H__
//******************************************************************************
class cxServiceManager : public cxServiceHandle
{
public:
	explicit cxServiceManager			(DWORD Access = SC_MANAGER_ALL_ACCESS);

public:
	SC_HANDLE	OpenService				(
		LPCTSTR			lpServiceName,
		DWORD			dwDesiredAccess		= SERVICE_ALL_ACCESS
		);

	SC_HANDLE	CreateService			(
		LPCTSTR			lpServiceName,
		LPCTSTR			lpDisplayName,
		DWORD			dwDesiredAccess,
		DWORD			dwServiceType,
		DWORD			dwStartType,
		DWORD			dwErrorControl,
		LPCTSTR			lpPath,
		LPCTSTR			lpLoadOrderGroup	= NULL,
		LPCTSTR			lpDependencies		= NULL,
		LPCTSTR			lpServiceStartName	= NULL,
		LPCTSTR			lpPassword			= NULL
		);
};
//******************************************************************************
#endif
