//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __ServiceImplement_H__
#define __ServiceImplement_H__
//******************************************************************************
#include "ServiceInstaller.h"
//******************************************************************************
enum {
	ServiceDefaultControls = SERVICE_ACCEPT_STOP |
		SERVICE_ACCEPT_SHUTDOWN |
		SERVICE_ACCEPT_PAUSE_CONTINUE |
		SERVICE_ACCEPT_POWEREVENT |
		SERVICE_ACCEPT_SESSIONCHANGE,
};
//******************************************************************************
class cxServiceImplement
{
public:
	cxServiceImplement(void);
	virtual ~cxServiceImplement(void);

public:
	virtual int WinMain(DWORD dwArgc, LPTSTR* lpszArgv);
	virtual DWORD ServiceHandler(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData);

public:
	virtual bool OnStart(DWORD dwArgc, LPTSTR* lpszArgv) { return true; }
	virtual void OnStop(void) {}
	virtual void OnPause(void) {}
	virtual void OnContinue(void) {}
	virtual void OnShutdown(void) {}
	virtual void OnPowerEvent(DWORD dwType) {}
	virtual void OnSessionEvent(DWORD dwType, DWORD dwSessionId) {}

public:
	bool ControlService(DWORD dwArgc, LPTSTR* lpszArgv);
	bool StartDispatcher(void);
	bool ChangeStatus(DWORD Status);

protected:
	bool InstallService(void);
	bool StartService(void);
	bool StopService(void);
	bool RemoveService(void);
	bool DebugService(void);
	bool InstallAndStart(void);

private:
	static void WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);

protected:
	CString m_ServiceName;
	CString m_DisplayName;
	CString m_Description;
	SERVICE_STATUS m_ServiceStatus;
	SERVICE_STATUS_HANDLE m_ServiceStatusHandle;
};
//******************************************************************************
#endif
