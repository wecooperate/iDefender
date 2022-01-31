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
#include "UIWidget.h"
#include <QDesktopWidget>
//******************************************************************************
UIWidgetHelper::UIWidgetHelper(QWidget* target)
	: m_Widget(target)
{
}
//******************************************************************************
void UIWidgetHelper::CenterWindow(int width, int height, QWidget* parent)
{
	QDesktopWidget desktop_widget;

	int desktop_width = desktop_widget.availableGeometry().width();
	int desktop_height = desktop_widget.availableGeometry().height();

	if (width > desktop_width || height > desktop_height) {
		m_Widget->setGeometry(0, 0, desktop_width, desktop_height);
		return;
	}

	if (!parent) {
		parent = m_Widget->parentWidget();
	}

	if (!parent) {
		m_Widget->setGeometry(desktop_width / 2 - width / 2, desktop_height / 2 - height / 2, width, height);
		return;
	}

	QPoint pos = parent->mapToGlobal(QPoint(0, 0));
	int x = pos.x() + (parent->width() - width) / 2;
	int y = pos.y() + (parent->height() - height) / 2;

	m_Widget->setGeometry(x, y, width, height);
}
//******************************************************************************
