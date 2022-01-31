//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIRuleView_3F1C6EF8_D2AA_4233_B89E_63A7EB02F27E__
#define __UIRuleView_3F1C6EF8_D2AA_4233_B89E_63A7EB02F27E__
//******************************************************************************
namespace Ui {
class UIRuleView;
}
//******************************************************************************
class UIRuleView : public QWidget
{
	Q_OBJECT

public:
	explicit UIRuleView(QWidget* parent = nullptr);
	~UIRuleView();

private slots:
	void on_btnLocate_clicked();
	void on_btnDocument_clicked();

private:
	Ui::UIRuleView* ui;
};
//******************************************************************************
#endif
