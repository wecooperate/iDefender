//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __ShellDialog_h_e15d482f_6a0b_4c3c_a3c5_534747c71e34__
#define __ShellDialog_h_e15d482f_6a0b_4c3c_a3c5_534747c71e34__
//******************************************************************************
#include <third_party/shadow/ShadowWindow.h>
//******************************************************************************
namespace Ui {
class UIShellDialog;
}
//******************************************************************************
class UIShellDialog
	: public QShadowDialogWidget
	, public UIWidgetHelper
{
	Q_OBJECT

public:
	UIShellDialog(QWidget* parent = nullptr);
	~UIShellDialog();

protected:
	void Initialize();
	void SetMainWidget(QWidget* widget);
	void SetLogoIcon(QChar index);
	void SetTitle(const QString& title);

protected:
	void changeEvent(QEvent* event) override;

private slots:
	void on_btnMenu_Min_clicked();
	void on_btnMenu_Max_clicked();
	void on_btnMenu_Close_clicked();

protected:
	Ui::UIShellDialog* ui;
};
//******************************************************************************
#endif
