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
#include "UIStyle.h"
#include <QFileInfo>
//******************************************************************************
void UIStyle::LoadStyleSheet(const QString& defaultQss, const QString& fileQss)
{
	QString path_qss = defaultQss;

	QFileInfo fileInfo(fileQss);
	if (fileInfo.isFile()) {
		path_qss = fileQss;
	}

	QFile file_base_qss(":/base/res/qss/default.css");
	QFile file_qss(path_qss);

	QString qss;

	if (file_base_qss.open(QFile::ReadOnly)) {
		qss += QLatin1String(file_base_qss.readAll());
		qss += "\r\n";
		file_base_qss.close();
	}

	if (file_qss.open(QFile::ReadOnly)) {
		qss += QLatin1String(file_qss.readAll());
		qss += "\r\n";
		file_qss.close();
	}

	qApp->setStyleSheet(qss);
}
//******************************************************************************
