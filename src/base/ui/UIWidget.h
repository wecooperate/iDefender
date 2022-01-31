//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __WidgetHelper_h_a8cbb5ce_d9b7_4fd2_a97e_0af36550348d__
#define __WidgetHelper_h_a8cbb5ce_d9b7_4fd2_a97e_0af36550348d__
//******************************************************************************
class UIWidgetHelper
{
public:
	UIWidgetHelper(QWidget* target);

public:
	void CenterWindow(int width, int height, QWidget* parent = nullptr);

protected:
	QWidget* m_Widget;
};
//******************************************************************************
#endif
