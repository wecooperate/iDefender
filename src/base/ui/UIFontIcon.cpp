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
#include "UIFontIcon.h"
#include <QFontDatabase>
#include <QPainter>
//******************************************************************************
UIFontIcon::UIFontIcon(void)
{
	int fontId = QFontDatabase::addApplicationFont(":/base/res/fontawesome-webfont.ttf");
	QStringList fontName = QFontDatabase::applicationFontFamilies(fontId);

	if (fontName.count() > 0) {
		m_IconFont = QFont(fontName.at(0));
	} else {
		DCHECK(!"invalid font");
	}
}
//******************************************************************************
QPixmap UIFontIcon::CreatePixmap(const QString& color, QChar index, uint32_t size, uint32_t width, uint32_t height)
{
	QPixmap pixmap(width, height);
	pixmap.fill(Qt::transparent);

	QPainter painter;
	painter.begin(&pixmap);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.setPen(QColor(color));
	painter.setBrush(QColor(color));

	m_IconFont.setPointSize(size);
	painter.setFont(m_IconFont);
	painter.drawText(pixmap.rect(), Qt::AlignCenter, index);
	painter.end();

	return pixmap;
}
//******************************************************************************
QIcon UIFontIcon::CreateIcon(const QString& color, QChar index, uint32_t size, uint32_t width, uint32_t height)
{
	QIcon icon;
	icon.addPixmap(CreatePixmap(color, index, size, width, height));
	return icon;
}
//******************************************************************************
