//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIConfigServiceImpl_3666E2C1_5F6E_404C_82FF_5C87777EAA6F__
#define __UIConfigServiceImpl_3666E2C1_5F6E_404C_82FF_5C87777EAA6F__
//******************************************************************************
#include <base/ui/service/Config/UIConfigServiceImpl.h>
//******************************************************************************
class UIConfigServiceImpl : public UIConfigServiceImplBase
{
public:
	UIConfigServiceImpl(void);
};
//******************************************************************************
UI_SERVICE_REGISTER(UIConfigService, UIConfigServiceImpl)
//******************************************************************************
#endif
