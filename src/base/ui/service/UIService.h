//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __IService_7578747C_2A2E_42C2_9270_35C25EAC3254__
#define __IService_7578747C_2A2E_42C2_9270_35C25EAC3254__
//******************************************************************************
interface UIService;
interface UIServiceManager;
//******************************************************************************
interface UIServiceEventHandler
{
	virtual void OnEvent(int32_t event, void* data) = 0;
};
//******************************************************************************
interface UIServiceEventManager
{
	virtual void RegisterHandler(int32_t event, UIServiceEventHandler * handler) = 0;
	virtual void UnregisterHandler(int32_t event, UIServiceEventHandler * handler) = 0;
	virtual void FireEvent(int32_t event, void* data) = 0;
};
//******************************************************************************
interface UIService : public UIServiceEventHandler
{
	virtual ~UIService(void) = default;

	virtual void Initialize(UIServiceManager * service_manager) = 0;
	virtual void Uninitialize(void) = 0;
};
//******************************************************************************
interface UIServiceManager : public UIServiceEventManager
{
	virtual ~UIServiceManager(void) = default;

	virtual UIService* GetService(const char* name) const = 0;
};
//******************************************************************************
UIServiceManager* UIServiceManagerInstance();
//******************************************************************************
#endif
