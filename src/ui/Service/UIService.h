//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIService_7C0D19C0_6ED8_41E3_A416_305BEF28CC13__
#define __UIService_7C0D19C0_6ED8_41E3_A416_305BEF28CC13__
//******************************************************************************
#include "Config/UIConfigServiceImpl.h"
//******************************************************************************
#define UI_ALL_SERVICE(def) \
	def(ConfigService)

#define UI_SERVIDE_DEF_GET(name) \
	UI##name* Get##name() { return GetService<UI##name>(); }
//******************************************************************************
#endif
