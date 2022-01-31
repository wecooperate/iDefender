//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __ServiceInstaller_H__
#define __ServiceInstaller_H__
//******************************************************************************
class cxServiceInstaller
{
#define g_ServiceInstaller SINGLETON_(cxServiceInstaller)

public:
	bool IsServiceInstalled(LPCTSTR lpServiceName);
	HRESULT InstallService(LPCTSTR lpServiceName, LPCTSTR lpDisplayName, LPCTSTR lpPath);
	HRESULT StartService(LPCTSTR lpServiceName);
	HRESULT StopService(LPCTSTR lpServiceName);
	HRESULT RemoveService(LPCTSTR lpServiceName);
	HRESULT SetConfig(LPCTSTR lpServiceName, DWORD dwType, PVOID lpInfo);
};
//******************************************************************************
#endif
