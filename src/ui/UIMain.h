//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __MainWindow_h_1b4407b3_34d3_44b6_a959_66d3cae7bbf9__
#define __MainWindow_h_1b4407b3_34d3_44b6_a959_66d3cae7bbf9__
//******************************************************************************
class UIMainWindow : public UIShellWindow
{
	Q_OBJECT
public:
	UIMainWindow(QWidget* parent);

protected:
	void closeEvent(QCloseEvent* event) override;

protected:
	QIcon MakeIcon(QChar index);
	void LoadStyleSheet(void);
};
//******************************************************************************
#endif
