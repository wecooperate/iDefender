//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIStyle_5CBD86AE_48A3_45D7_B6E0_0E8E916575C4__
#define __UIStyle_5CBD86AE_48A3_45D7_B6E0_0E8E916575C4__
//******************************************************************************
class UIStyle
{
#define g_UIStyle SINGLETON_(UIStyle)

public:
	void LoadStyleSheet(const QString& defaultQss, const QString& fileQss);
};
//******************************************************************************
#endif
