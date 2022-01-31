//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIHomeView_h_40c0532c_fb2c_4ccd_ad73_d93e515146f0__
#define __UIHomeView_h_40c0532c_fb2c_4ccd_ad73_d93e515146f0__
//******************************************************************************
namespace Ui {
class UIHomeView;
}
//******************************************************************************
class UIHomeView : public QWidget
{
	Q_OBJECT

public:
	explicit UIHomeView(QWidget* parent = nullptr);
	~UIHomeView();

protected:
	void UpdateState(bool showError);
	void ExecuteServiceCommand(LPCTSTR Command);

private slots:
	void on_btnStart_clicked();

private:
	bool m_Started = false;
	Ui::UIHomeView* ui;
};
//******************************************************************************
#endif
