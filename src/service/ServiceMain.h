//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __ServiceMain_H__
#define __ServiceMain_H__
//******************************************************************************
#include "ServiceImplement\ServiceImplement.h"
#include "Defender.h"
//******************************************************************************
class cxServcieMain : public cxServiceImplement
{
#define g_ServiceMain SINGLETON_(cxServcieMain)

public:
	cxServcieMain(void);

public:
	virtual bool OnStart(DWORD dwArgc, LPTSTR* lpszArgv);
	virtual void OnStop(void);

protected:
	cxHandle m_InstanceMutex;
	cxDefender m_Defender;
};
//******************************************************************************
#endif
