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
#include "Defender.h"
#include "DefenderDatabase.h"
//******************************************************************************
HRESULT cxDefender::Start(void)
{
	HRESULT hr = m_MonitorManager.Start(this);

	if (hr != S_OK) {
		return hr;
	}

	cxMSGUserSetSessionConfig config;
	config.FilterFileCloseOnlyModified = TRUE;
	config.FilterFileCreateOnlyModifiable = TRUE;
	m_MonitorManager.InControl(config);

	return LoadRules();
}
//******************************************************************************
void cxDefender::Stop(void)
{
	m_MonitorManager.Stop();
}
//******************************************************************************
void cxDefender::OnCallback(IMonitorMessage* Message)
{
	if (Message->GetType() == emMSGFileCleanup) {
		cxMSGFileCleanup* msg = (cxMSGFileCleanup*)Message;

		if (!msg->IsMatchPath(m_RulePath))
			return;

		LoadRules(true);

		return;
	}

	if (!m_RuleEngine)
		return;

	m_RuleEngine->Match(Message, this);
}
//******************************************************************************
IMonitorRuleCallback::emMatchStatus cxDefender::OnMatch(IMonitorMessage* Message, const MatchResult& Result)
{
	if (!(Result.Action & emMSGActionBlock))
		return emMatchStatusContinue;

	std::shared_ptr<cxDefenderEvent> event = std::make_shared<cxDefenderEvent>();
	event->Time = Message->GetHeader()->Time;
	event->EventType = Message->GetType();
	event->EventName = Message->GetTypeName();
	event->ProcessId = Message->GetCurrentProcessId();
	event->ProcessPath = Message->GetString(emMSGFieldCurrentProcessPath);
	event->ProcessName = Message->GetString(emMSGFieldCurrentProcessName);
	event->ProcessCommandline = Message->GetString(emMSGFieldCurrentProcessCommandline);
	event->RuleGroup = CA2T(Result.GroupName, CP_UTF8);
	event->RuleName = CA2T(Result.RuleName, CP_UTF8);

	switch (Message->GetType()) {
	case emMSGSocketConnect:
	case emMSGSocketSend:
	case emMSGSocketSendTo:
	case emMSGSocketListen: {
		cxMSGSocketConnect* msg = (cxMSGSocketConnect*)Message;
		ULONG ip = msg->IP();
		ULONG port = msg->Port();
		event->TargetPath.Format(_T("%d.%d.%d.%d:%d"),
			((PUCHAR)&ip)[0],
			((PUCHAR)&ip)[1],
			((PUCHAR)&ip)[2],
			((PUCHAR)&ip)[3],
			ntohs(port));
	} break;

	default:
		event->TargetPath = Message->GetString(emMSGFieldPath);
		break;
	}

	g_MainLooper->PostRunnable([this, event]() {
		this->OnDefenderEvent(event);
	});

	Message->SetBlock();

	return emMatchStatusBreak;
}
//******************************************************************************
void cxDefender::OnDefenderEvent(std::shared_ptr<cxDefenderEvent> Event)
{
	CString event_str;
	event_str.Format(_T("%s|%s|%s"), Event->ProcessName, Event->EventName, Event->TargetPath);
	event_str.MakeLower();
	std::string event_ansi_str = CT2A(event_str, CP_UTF8);

	cxHashMD5 event_hash;
	event_hash.Update((const unsigned char*)event_ansi_str.c_str(), event_ansi_str.length());

	Event->EventId = event_hash.Finish().ToString();

	SPDLOG_INFO("[{}.{}] {} [{}] {}",
		Event->RuleGroup,
		Event->RuleName,
		Event->ProcessName,
		Event->EventName,
		Event->TargetPath);

	g_DefenderDatabase->Insert(Event);
}
//******************************************************************************
HRESULT cxDefender::LoadRules(bool Reload)
{
	if (Reload) {
		SPDLOG_INFO("begin reload rules");
		m_RuleEngine.Release();
	}

	if (m_RulePath.IsEmpty()) {
		m_RulePath = g_Path->GetCurrentPath(_T("rules\\*.json")).GetString();
	}

	m_RuleEngine = m_MonitorManager.CreateRuleEngine(m_RulePath);

	if (!m_RuleEngine) {
		SPDLOG_ERROR("laod rule failed");
		return E_UNEXPECTED;
	}

	SPDLOG_INFO("load rule success");

	cxMSGUserSetMSGConfig config;
	m_RuleEngine->EnumAffectedMessage(
		[](ULONG Type, void* Context) {
			SPDLOG_INFO("affected type = {}", Type);
			cxMSGUserSetMSGConfig* config_ptr = (cxMSGUserSetMSGConfig*)Context;
			config_ptr->Config[Type] = emMSGConfigSend;
		},
		&config);

	config.Config[emMSGFileCleanup] = emMSGConfigPost;

	return m_MonitorManager.InControl(config);
}
//******************************************************************************
