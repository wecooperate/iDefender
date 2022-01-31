//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __Service_H__
#define __Service_H__
//******************************************************************************
class cxService : public cxServiceHandle
{
public:
	using cxServiceHandle::cxServiceHandle;

public:
	cxService					(SC_HANDLE SCMHandle, LPCTSTR Name, DWORD Access = SERVICE_ALL_ACCESS);

public:
	HRESULT		Open			(SC_HANDLE SCMHandle, LPCTSTR Name, DWORD Access = SERVICE_ALL_ACCESS);
	HRESULT		Start			(DWORD dwNumServiceArgs = 0, LPCTSTR* lpServiceArgVectors = NULL);
	HRESULT		Stop			(void);
	HRESULT		Delete			(void);
	HRESULT		Control			(DWORD dwControl, LPSERVICE_STATUS lpServiceStatus = NULL);
	HRESULT		SetConfigEx		(DWORD dwInfoLevel, PVOID lpInfo);
	HRESULT		WaitAndTerminate(ULONG msTimeout);

public:
	HRESULT		QueryConfig		(
		LPQUERY_SERVICE_CONFIG	lpServiceConfig,
		DWORD					cbBufSize,
		LPDWORD					pcbBytesNeeded
		);

	HRESULT		QueryConfigEx	(
		DWORD					dwInfoLevel,
		LPBYTE					lpServiceConfig,
		DWORD					cbBufSize,
		LPDWORD					pcbBytesNeeded
		);

	HRESULT		QueryStatus		(LPSERVICE_STATUS lpStatus);
	HRESULT		QueryStatusProcess(LPSERVICE_STATUS_PROCESS lpStatus);

public:
	SERVICE_STATUS			GetStatus	(void);
};
//******************************************************************************
#endif
