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
#include "UIManager.h"
#include "UIMain.h"
//******************************************************************************
UIServiceManager* UIServiceManagerInstance()
{
	return g_UIManager;
}
//******************************************************************************
void UIViewManager::Show(const std::string& name, bool modal)
{
	auto view = GetView(name);

	if (name != SCHEME_MAIN_VIEW) {
		view->setParent(GetView(SCHEME_MAIN_VIEW), Qt::Window);
	}

	if (modal) {
		if (auto dialog = qobject_cast<QDialog*>(view)) {
			dialog->setModal(true);
		}
	}

	view->show();
}
//******************************************************************************
QWidget* UIViewManager::GetView(const std::string& name)
{
	auto it = m_ViewCreators.find(name);

	if (it != m_ViewCreators.end()) {
		auto& creator = it->second;

		if (!creator.Singleton) {
			auto widget = creator.Create();
			widget->setAttribute(Qt::WA_DeleteOnClose, true);
			return widget;
		}

		if (!creator.Instance) {
			creator.Instance = creator.Create();
		}

		return creator.Instance;
	}

	return nullptr;
}
//******************************************************************************
UIManager::UIManager(void)
{
	connect(
		this, &UIManager::UIExecute, this, [](std::function<void()> Runnable) {
			Runnable();
		},
		Qt::BlockingQueuedConnection);

	RegisterViewCreator<UIMainWindow>(SCHEME_MAIN_VIEW);
}
//******************************************************************************
void UIManager::Initialize(void)
{
	m_Initialized = true;

	InitializeService();

	Show(SCHEME_MAIN_VIEW);
}
//******************************************************************************
void UIManager::Uninitialize(void)
{
	m_Initialized = false;

	UninitializeService();
	ClearEventHandler();
}
//******************************************************************************
bool UIManager::IsUIThreand(void)
{
	return m_CurrentThreadId == std::this_thread::get_id();
}
//******************************************************************************
void UIManager::FireEvent(int32_t event, void* data)
{
	if (!m_Initialized)
		return;

	if (!IsUIThreand()) {
		emit UIExecute([&]() {
			FireEvent(event, data);
		});
		return;
	}

	UIServiceManagerImpl::FireEvent(event, data);
}
//******************************************************************************
