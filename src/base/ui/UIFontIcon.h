//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __IconHelper_h_7b17b9c0_c51b_4540_835f_ece7ecc01f60__
#define __IconHelper_h_7b17b9c0_c51b_4540_835f_ece7ecc01f60__
//******************************************************************************
#include "stdafx.h"
//******************************************************************************
enum emFontIcon {
	emFontIconMenu = 0xf0d7,
	emFontIconMin = 0xf068,
	emFontIconMax = 0xf2d2,
	emFontIconNormal = 0xf2d0,
	emFontIconClose = 0xf00d,
};
//******************************************************************************
class UIFontIcon
{
#define g_UIFontIcon SINGLETON_(UIFontIcon)

public:
	UIFontIcon(void);

public:
	QPixmap CreatePixmap(const QString& color, QChar index, uint32_t size = 9, uint32_t width = 10, uint32_t height = 10);
	QIcon CreateIcon(const QString& color, QChar index, uint32_t size = 9, uint32_t width = 10, uint32_t height = 10);

public:
	template<typename TWidget>
	void SetFontIcon(TWidget* widget, QChar index, uint32_t size = 9)
	{
		m_IconFont.setPointSize(size);
		widget->setFont(m_IconFont);
		widget->setText(index);
	}

private:
	QFont m_IconFont;
};
//******************************************************************************
#endif
