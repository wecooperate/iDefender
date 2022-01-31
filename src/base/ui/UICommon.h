//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UICommon_30CD153B_34AE_40FD_889A_292954F0AD7B__
#define __UICommon_30CD153B_34AE_40FD_889A_292954F0AD7B__
//******************************************************************************
class UICommon
{
#define g_UICommon SINGLETON_(UICommon)

public:
	void LoadConfig(QWidget* widget);
	void SaveConfig(QWidget* widget);

public:
	void InitTreeView(QTreeView* view);
};
//******************************************************************************
template<typename T>
class UIConfigurableWidget : public T
{
public:
	UIConfigurableWidget(QWidget* parent = nullptr)
		: T(parent)
	{
		g_UICommon->LoadConfig(this);
	}

	void closeEvent(QCloseEvent* event) override
	{
		g_UICommon->SaveConfig(this);

		T::closeEvent(event);
	}

	__if_exists(T::done)
	{
		void done(int result) override
		{
			T::done(result);
			close();
		}
	}
};
//******************************************************************************
#endif
