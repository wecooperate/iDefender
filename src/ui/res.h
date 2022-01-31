//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __res_h_b3fe7196_b47f_415e_b8cc_c285c45d7b86__
#define __res_h_b3fe7196_b47f_415e_b8cc_c285c45d7b86__
//******************************************************************************
class UIResource
{
#define g_res SINGLETON_(UIResource)

public:
	QIcon icon_main = QIcon(":/res/main.ico");
	QIcon icon_msg_other = QIcon(":/res/O.ico");
	QIcon icon_msg_file = QIcon(":/res/F.ico");
	QIcon icon_msg_process = QIcon(":/res/P.ico");
	QIcon icon_msg_network = QIcon(":/res/N.ico");
	QIcon icon_msg_registry = QIcon(":/res/R.ico");
};
//******************************************************************************
#endif
