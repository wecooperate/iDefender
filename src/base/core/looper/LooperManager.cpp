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
#include "LooperManager.h"
#include "UILooper.h"
//******************************************************************************
template<typename T>
class cxThreadLocalStorage
{
public:
	cxThreadLocalStorage(void)
	{
		m_Index = TlsAlloc();
	}

	inline T* Get(void)
	{
		return reinterpret_cast<T*>(TlsGetValue(m_Index));
	}

	inline bool Set(T* Value)
	{
		return TlsSetValue(m_Index, Value);
	}

protected:
	DWORD m_Index = -1;
};
//******************************************************************************
static cxThreadLocalStorage<ILooper> g_LooperLocalStorage;
//******************************************************************************
void cxLooperManager::Start(bool MainThread)
{
	if (MainThread) {
		auto looper = std::make_shared<cxUIMainThreadLooper>();
		looper->Start();
		m_MainLooper = looper;
	} else {
		m_MainLooper = CreateLooper(ILooper::kUILooper, "main");
	}

	m_WorkerLooper = CreateLooper(ILooper::kUILooper, "worker");
}
//******************************************************************************
void cxLooperManager::Stop(void)
{
	if (m_MainLooper) {
		m_MainLooper->Terminate();
		m_MainLooper.reset();
	}

	if (m_WorkerLooper) {
		m_WorkerLooper->Terminate();
		m_WorkerLooper.reset();
	}
}
//******************************************************************************
std::shared_ptr<ILooper> cxLooperManager::GetMainLooper(void)
{
	return m_MainLooper;
}
//******************************************************************************
std::shared_ptr<ILooper> cxLooperManager::GetWorkerLooper()
{
	return m_WorkerLooper;
}
//******************************************************************************
template<typename T>
std::shared_ptr<ILooper> DoCreateLooper(std::string_view Name)
{
	auto looper = std::make_shared<cxLooperThread_<T>>();
	looper->Start(Name);
	return looper;
}
//******************************************************************************
std::shared_ptr<ILooper> cxLooperManager::CreateLooper(ILooper::LooperType Type, std::string_view Name)
{
	switch (Type) {
	case ILooper::kUILooper:
		return DoCreateLooper<cxUILooper>(Name);

	default:
		DCHECK(!"not support looper type");
		return nullptr;
	}
}
//******************************************************************************
bool cxLooperManager::IsCurrent(ILooper* Looper)
{
	return g_LooperLocalStorage.Get() == Looper;
}
//******************************************************************************
bool cxLooperManager::IsCurrent(std::shared_ptr<ILooper> Looper)
{
	return IsCurrent(Looper.get());
}
//******************************************************************************
void cxLooperManager::SetCurrent(ILooper* Looper)
{
	g_LooperLocalStorage.Set(Looper);
}
//******************************************************************************
ILooper* cxLooperManager::Current(void)
{
	return g_LooperLocalStorage.Get();
}
//******************************************************************************
