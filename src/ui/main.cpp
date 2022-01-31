//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "UIManager.h"
#include <QTranslator>
//******************************************************************************
int UIStartup(void)
{
	g_Looper->Start(true);

	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication app(__argc, __argv);

	Q_INIT_RESOURCE(base);
	Q_INIT_RESOURCE(res);

	if (QLocale().language() == QLocale::Chinese) {
		QTranslator* translator = new QTranslator();
		translator->load(":/res/language/zh_cn.qm");
		qApp->installTranslator(translator);
	}

	g_UIManager->Initialize();

	return app.exec();
}
//******************************************************************************
