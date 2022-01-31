//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __DefenderEvent_914E5600_8000_4F5F_95CD_AC3C8BED4FA0__
#define __DefenderEvent_914E5600_8000_4F5F_95CD_AC3C8BED4FA0__
//******************************************************************************
struct cxDefenderEvent
{
	ULONGLONG Time;
	CString EventId;
	ULONG EventType;
	CString EventName;
	ULONG ProcessId;
	CString ProcessPath;
	CString ProcessName;
	CString ProcessCommandline;
	CString TargetPath;
	CString RuleGroup;
	CString RuleName;
};
//******************************************************************************
#endif
