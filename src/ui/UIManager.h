//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIManager_93A042E3_72F1_4294_9636_53D58EE3B135__
#define __UIManager_93A042E3_72F1_4294_9636_53D58EE3B135__
//******************************************************************************
#include "Service/UIService.h"
//******************************************************************************
#define SCHEME_MAIN_VIEW "iDefender://Main"
//******************************************************************************
class UIViewManager
{
public:
	void Show(const std::string& name, bool modal = false);

	QWidget* GetView(const std::string& name);

	template<typename T>
	T* GetView(const char* name)
	{
		return qobject_cast<T*>(GetView(name));
	}

protected:
	struct ViewCreator
	{
		bool Singleton;
		QWidget* Instance;
		std::function<QWidget*(void)> Create;
	};

	template<typename T>
	void RegisterViewCreator(const char* name, bool singleton = true)
	{
		ViewCreator creator;

		creator.Singleton = singleton;
		creator.Instance = nullptr;
		creator.Create = []() {
			return new UIConfigurableWidget<T>();
		};

		m_ViewCreators.insert(std::make_pair(name, std::move(creator)));
	}

protected:
	std::map<std::string, ViewCreator> m_ViewCreators;
};
//******************************************************************************
class UIManager
	: public QObject
	, public UIServiceManagerImpl
	, public UIViewManager
{
	Q_OBJECT

#define g_UIManager SINGLETON_(UIManager)

public:
	UIManager(void);

public:
	UI_ALL_SERVICE(UI_SERVIDE_DEF_GET)

	template<typename T>
	inline T* GetService() const
	{
		static T* service = dynamic_cast<T*>(UIServiceManagerImpl::GetService(T::NAME));

		return service;
	}

public:
	void Initialize(void);
	void Uninitialize(void);

public:
	void FireEvent(int32_t event, void* data) override;

protected:
	bool IsUIThreand(void);

signals:
	void UIExecute(std::function<void()> Runnable);

private:
	bool m_Initialized = false;
	std::thread::id m_CurrentThreadId = std::this_thread::get_id();
};
//******************************************************************************
#endif
