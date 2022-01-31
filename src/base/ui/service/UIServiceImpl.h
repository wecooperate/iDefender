//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIService_FA8DA1B9_7669_4903_B98C_C6BA7DCE6363__
#define __UIService_FA8DA1B9_7669_4903_B98C_C6BA7DCE6363__
//******************************************************************************
#include "UIService.h"
//******************************************************************************
template<typename TBase>
class UIServiceClientBase : public TBase
{
public:
	static constexpr auto SERVICE_ALL_EVENT = 0;

public:
	template<typename T>
	inline T* GetService() const
	{
		T* service = dynamic_cast<T*>(m_ServiceManager->GetService(T::NAME));

		return service;
	}

public:
	void OnEvent(int32_t event, void* data) override
	{
		auto it = m_EventHandlers.find(event);

		if (it != m_EventHandlers.end()) {
			it->second(data);
		}
	}

	template<typename T>
	void HandleEvent(int32_t event, T&& handler)
	{
		m_ServiceManager->RegisterHandler(event, this);

		if constexpr (lambda_type<T>::arity > 0) {
			m_EventHandlers[event] = [handler](void* data) {
				handler(*(typename lambda_type<T>::arg<0>::type*)data);
			};
		} else {
			m_EventHandlers[event] = [handler](void* data) {
				handler();
			};
		}
	}

	template<typename T>
	inline void HandleEvent(T&& handler)
	{
		if constexpr (lambda_type<T>::arity > 0) {
			HandleEvent(lambda_type<T>::arg<0>::type::NAME, std::move(handler));
		}
	}

	template<typename T>
	inline void FireEvent(T& event)
	{
		if (m_ServiceManager) {
			m_ServiceManager->FireEvent(T::NAME, &event);
		}
	}

	inline void FireEvent(int32_t event)
	{
		if (m_ServiceManager) {
			m_ServiceManager->FireEvent(event, nullptr);
		}
	}

protected:
	UIServiceManager* m_ServiceManager = nullptr;
	std::map<int32_t, std::function<void(void*)>> m_EventHandlers;
};
//******************************************************************************
template<typename TService = UIService>
class UIServiceImplBase : public UIServiceClientBase<TService>
{
public:
	void Initialize(UIServiceManager* service_manager) override
	{
		m_ServiceManager = service_manager;

		Initialize();
	}

	void Uninitialize(void) override
	{
		m_ServiceManager->UnregisterHandler(SERVICE_ALL_EVENT, this);

		m_ServiceManager = nullptr;
	}

	virtual void Initialize(void) {}
};
//******************************************************************************
class UIServiceCreatorManager
{
#define g_UIServiceCreatorManager SINGLETON_(UIServiceCreatorManager)

public:
	using UIServiceCreator = std::function<std::shared_ptr<UIService>()>;

public:
	void InsertCreator(const std::string& name, UIServiceCreator creator)
	{
		m_Creators.insert(std::make_pair(name, creator));
	}

public:
	const std::map<std::string, UIServiceCreator>& GetCreators(void)
	{
		return m_Creators;
	}

protected:
	std::map<std::string, UIServiceCreator> m_Creators;
};
//******************************************************************************
template<typename TInterface, typename TClass>
class UIServiceRegister
{
public:
	UIServiceRegister()
	{
		g_UIServiceCreatorManager->InsertCreator(TInterface::NAME, []() {
			return std::make_shared<TClass>();
		});
	}
};
//******************************************************************************
#ifdef _M_IX86
#define pragma_include_(_x_) __pragma(comment(linker, "/include:_" #_x_))
#else
#define pragma_include_(_x_) __pragma(comment(linker, "/include:" #_x_))
#endif
//******************************************************************************
#define UI_SERVICE_REGISTER(interface, class)                                                                 \
	extern "C" __declspec(selectany) UIServiceRegister<interface, class> __service_##interface##_##class##__; \
	pragma_include_(__service_##interface##_##class##__);
//******************************************************************************
class UIServiceManagerImpl : public UIServiceManager
{
public:
	UIServiceManagerImpl()
	{
		for (auto& it : g_UIServiceCreatorManager->GetCreators()) {
			RegisterService(it.first, it.second());
		}
	}

public:
	void RegisterService(const std::string& name, std::shared_ptr<UIService> service)
	{
		if (name.empty() || !service)
			return;

		m_Services.insert(std::make_pair(name, service));
	}

	template<typename T>
	void RegisterService()
	{
		RegisterService(T::NAME, std::make_shared<T>());
	}

	UIService* GetService(const char* name) const override
	{
		auto it = m_Services.find(name);

		return it == m_Services.end() ? nullptr : it->second.get();
	}

	template<typename T>
	inline T* GetService() const
	{
		return dynamic_cast<T*>(GetService(T::NAME));
	}

public:
	void RegisterHandler(int32_t event, UIServiceEventHandler* handler) override
	{
		for (auto it = m_EventHandlers.lower_bound(event); it != m_EventHandlers.upper_bound(event); it++) {
			if (it->second == handler)
				return;
		}

		m_EventHandlers.insert(std::make_pair(event, handler));
	}

	void UnregisterHandler(int32_t event, UIServiceEventHandler* handler) override
	{
		for (auto it = m_EventHandlers.begin(); it != m_EventHandlers.end();) {
			if (it->second == handler) {
				if (event == 0 || event == it->first) {
					it = m_EventHandlers.erase(it);
					continue;
				}
			}
			it++;
		}
	}

	void FireEvent(int32_t event, void* data) override
	{
		for (auto it = m_EventHandlers.lower_bound(event); it != m_EventHandlers.upper_bound(event); it++) {
			it->second->OnEvent(event, data);
		}
	}

	void ClearEventHandler(void)
	{
		m_EventHandlers.clear();
	}

protected:
	void InitializeService(void)
	{
		for (auto& it : m_Services) {
			it.second->Initialize(this);
		}
	}

	void UninitializeService(void)
	{
		for (auto& it : m_Services) {
			it.second->Uninitialize();
		}
	}

protected:
	std::map<std::string, std::shared_ptr<UIService>> m_Services;
	std::multimap<int32_t, UIServiceEventHandler*> m_EventHandlers;
};
//******************************************************************************
#endif
