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
#include "UICommon.h"
#include "service/UIService.h"
#include <QCheckBox>
//******************************************************************************
void UICommon::LoadConfig(QWidget* widget)
{
	auto config_service = static_cast<UIConfigService*>(UIServiceManagerInstance()->GetService(UIConfigService::NAME));

	if (!config_service)
		return;

	auto name = widget->objectName();

	auto main_window = qobject_cast<QMainWindow*>(widget);
	if (main_window) {
		config_service->LoadState(main_window, name.toStdString().c_str());
	}

	config_service->LoadGeometry(widget, name.toStdString().c_str());

	for (auto& it : widget->findChildren<QTreeView*>()) {
		auto sub_name = name + '_' + it->objectName();
		config_service->LoadState(it->header(), sub_name.toStdString().c_str());
	}

	for (auto& it : widget->findChildren<QTabWidget*>()) {
		auto sub_name = name + '_' + it->objectName();
		auto index = config_service->GetSectionInt(sub_name.toStdString().c_str(), "index", -1);
		if (index != -1) {
			it->setCurrentIndex(index);
		}
	}

	for (auto& it : widget->findChildren<QCheckBox*>()) {
		auto sub_name = name + '_' + it->objectName();
		auto index = config_service->GetSectionInt(sub_name.toStdString().c_str(), "check", -1);
		if (index != -1) {
			it->setChecked(index);
		}
	}
}
//******************************************************************************
void UICommon::SaveConfig(QWidget* widget)
{
	auto config_service = static_cast<UIConfigService*>(UIServiceManagerInstance()->GetService(UIConfigService::NAME));

	if (!config_service)
		return;

	auto name = widget->objectName();

	auto main_window = qobject_cast<QMainWindow*>(widget);
	if (main_window) {
		config_service->SaveState(main_window, name.toStdString().c_str());
	}

	config_service->SaveGeometry(widget, name.toStdString().c_str());

	for (auto& it : widget->findChildren<QTreeView*>()) {
		auto sub_name = name + '_' + it->objectName();
		config_service->SaveState(it->header(), sub_name.toStdString().c_str());
	}

	for (auto& it : widget->findChildren<QTabWidget*>()) {
		auto sub_name = name + '_' + it->objectName();
		config_service->SetSectionInt(sub_name.toStdString().c_str(), "index", it->currentIndex());
	}

	for (auto& it : widget->findChildren<QCheckBox*>()) {
		auto sub_name = name + '_' + it->objectName();
		config_service->SetSectionInt(sub_name.toStdString().c_str(), "check", it->isChecked());
	}
}
//******************************************************************************
void UICommon::InitTreeView(QTreeView* view)
{
	view->setContextMenuPolicy(Qt::CustomContextMenu);
	view->setSelectionBehavior(QAbstractItemView::SelectRows);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	view->setSortingEnabled(true);
	view->setAlternatingRowColors(false);
	view->setAnimated(false);
	view->setUniformRowHeights(true);
	view->setTextElideMode(Qt::TextElideMode::ElideMiddle);
	view->setRootIsDecorated(false);
	view->header()->setStretchLastSection(true);
}
//******************************************************************************
