//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __DefenderDatabase_9946CB8E_CF40_432E_AA5E_CCC360E71D1F__
#define __DefenderDatabase_9946CB8E_CF40_432E_AA5E_CCC360E71D1F__
//******************************************************************************
#include <database/Database.h>
#include "DefenderEvent.h"
//******************************************************************************
class cxDefenderDatabase
{
#define g_DefenderDatabase SINGLETON_(cxDefenderDatabase)

public:
	cxDefenderDatabase(void);

public:
	void Insert(std::shared_ptr<cxDefenderEvent> Event);

protected:
	void Cleanup(void);

protected:
	cxAtomic m_InsertCount = 0;
	cxDatabase m_Database;
	cxDatabaseStatement m_InsertStatement;
	cxDatabaseStatement m_InsertDetailStatement;
};
//******************************************************************************
#endif
