//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __Defender_0E94BD9C_6FF2_4C04_B1F3_9023E1421539__
#define __Defender_0E94BD9C_6FF2_4C04_B1F3_9023E1421539__
//******************************************************************************
#include <iMonitorSDK.h>
#include <iMonitorProtocol.h>
#include "DefenderEvent.h"
//******************************************************************************
class cxDefender
	: public IMonitorCallback
	, public IMonitorRuleCallback
{
public:
	HRESULT Start(void);
	void Stop(void);

public:
	void OnCallback(IMonitorMessage* Message) override;
	emMatchStatus OnMatch(IMonitorMessage* Message, const MatchResult& Result) override;

protected:
	void OnDefenderEvent(std::shared_ptr<cxDefenderEvent> Event);

protected:
	HRESULT LoadRules(bool Reload = false);

protected:
	MonitorManager m_MonitorManager;
	CComPtr<IMonitorRuleEngine> m_RuleEngine;
	CString m_RulePath;
};
//******************************************************************************
#endif
