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
#include "UIShellDialog.h"
#include "ui_UIShellDialog.h"
#include <QDesktopWidget>
//******************************************************************************
UIShellDialog::UIShellDialog(QWidget* parent)
	: QShadowDialogWidget(true, 20, parent)
	, UIWidgetHelper(this)
	, ui(new Ui::UIShellDialog)
{
	QDialog* client_widget = new QDialog(this);
	ui->setupUi(client_widget);
	SetClientWidget(client_widget);

	Initialize();

	Q_CONNECT(ui->btnMenu_Close, clicked, on_btnMenu_Close_clicked);
	Q_CONNECT(ui->btnMenu_Max, clicked, on_btnMenu_Max_clicked);
	Q_CONNECT(ui->btnMenu_Min, clicked, on_btnMenu_Min_clicked);

	Q_CONNECT(client_widget, finished, done);
}
//******************************************************************************
UIShellDialog::~UIShellDialog()
{
	delete ui;
}
//******************************************************************************
void UIShellDialog::Initialize()
{
	g_UIFontIcon->SetFontIcon(ui->btnMenu_Min, emFontIconMin);
	g_UIFontIcon->SetFontIcon(ui->btnMenu_Max, emFontIconNormal);
	g_UIFontIcon->SetFontIcon(ui->btnMenu_Close, emFontIconClose);

	ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
	ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
	ui->buttonBox->button(QDialogButtonBox::Apply)->setText(tr("Apply"));

	CenterWindow(800, 500);
}
//******************************************************************************
void UIShellDialog::SetMainWidget(QWidget* widget)
{
	ui->layoutClient->addWidget(widget);
}
//******************************************************************************
void UIShellDialog::SetLogoIcon(QChar index)
{
	g_UIFontIcon->SetFontIcon(ui->labLogo, index, 12);
}
//******************************************************************************
void UIShellDialog::SetTitle(const QString& title)
{
	ui->labTitle->setText(title);
	setWindowTitle(title);
}
//******************************************************************************
void UIShellDialog::changeEvent(QEvent* event)
{
	if (windowState() == Qt::WindowMaximized) {
		g_UIFontIcon->SetFontIcon(ui->btnMenu_Max, emFontIconMax);
	} else if (windowState() == Qt::WindowNoState) {
		g_UIFontIcon->SetFontIcon(ui->btnMenu_Max, emFontIconNormal);
	}

	__super::changeEvent(event);
}
//******************************************************************************
void UIShellDialog::on_btnMenu_Min_clicked()
{
	showMinimized();
}
//******************************************************************************
void UIShellDialog::on_btnMenu_Max_clicked()
{
	SwitchMaximizeState();
}
//******************************************************************************
void UIShellDialog::on_btnMenu_Close_clicked()
{
	close();
}
//******************************************************************************
