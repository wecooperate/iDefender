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
#include "UIMain.h"
#include "View/UIHomeView.h"
#include "View/UIDefenderRecordView.h"
#include "View/UIRuleView.h"
#include <QShortcut>
//******************************************************************************
#define FONT_ICON_TITLE	   0xF260
#define FONT_ICON_HOME	   0xF015
#define FONT_ICON_RECORD   0xF0CA
#define FONT_ICON_RULE	   0xF044
#define FONT_ICON_ABOUT_US 0xF09B
//******************************************************************************
constexpr auto kAboutUsUrl = "https://github.com/wecooperate/iDefender";
//******************************************************************************
UIMainWindow::UIMainWindow(QWidget* parent)
{
	SetTitle(tr("iDefender"));
	SetTitleIcon(FONT_ICON_TITLE);
	ShowMenuButton(false);
	setWindowIcon(g_res->icon_main);

	InsertNavigatorButton<UIHomeView>(tr("Home"), MakeIcon(FONT_ICON_HOME));
	InsertNavigatorButton<UIDefenderRecordView>(tr("Event"), MakeIcon(FONT_ICON_RECORD));
	InsertNavigatorButton<UIRuleView>(tr("Rule"), MakeIcon(FONT_ICON_RULE));
	InsertNavigatorUrlButton(tr("AboutUs"), MakeIcon(FONT_ICON_ABOUT_US), kAboutUsUrl);

	Activate(tr("Home"));

#ifdef DEBUG
	QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_F5), this);
	connect(shortcut, &QShortcut::activated, [this]() {
		LoadStyleSheet();
	});
#endif

	LoadStyleSheet();

	auto database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(QApplication::applicationDirPath() + "/iDefender.db");
	database.open();
}
//******************************************************************************
void UIMainWindow::closeEvent(QCloseEvent* event)
{
	g_UIManager->Uninitialize();
}
//******************************************************************************
QIcon UIMainWindow::MakeIcon(QChar index)
{
	QIcon icon;
	icon.addPixmap(g_UIFontIcon->CreatePixmap("#6D7173", index, 20, 30, 30), QIcon::Normal);
	icon.addPixmap(g_UIFontIcon->CreatePixmap("#2774d8", index, 20, 30, 30), QIcon::Normal, QIcon::On);
	return icon;
}
//******************************************************************************
void UIMainWindow::LoadStyleSheet(void)
{
	QString path_qss = ":/res/qss/default.css";
	QString path_file = QApplication::applicationDirPath() + "/main.css";

	g_UIStyle->LoadStyleSheet(path_qss, path_file);
}
//******************************************************************************
