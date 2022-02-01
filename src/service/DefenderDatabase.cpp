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
#include "DefenderDatabase.h"
//******************************************************************************
constexpr auto kCleanupCount = 10000;
//******************************************************************************
static const char* sql_CreateTable = R"(
	CREATE TABLE IF NOT EXISTS defender_event(
		id INTEGER PRIMARY KEY AUTOINCREMENT
		, date DATE DEFAULT (date(CURRENT_TIMESTAMP, 'localtime'))
		, event_id TEXT NOT NULL
		, event_type INTEGER NOT NULL
		, event_name TEXT NOT NULL
		, process_name TEXT NOT NULL
		, process_path TEXT
		, process_commandline TEXT
		, target TEXT
		, rule_group_name TEXT
		, rule_name TEXT
		, count INTEGER DEFAULT 1
		, update_time DATETIME DEFAULT (datetime(CURRENT_TIMESTAMP, 'localtime'))
		, UNIQUE(date, event_id)
		);
	CREATE INDEX IF NOT EXISTS index_defender_event_date ON defender_event (date);
	CREATE INDEX IF NOT EXISTS index_defender_event_event_id ON defender_event (event_id);

	CREATE TABLE IF NOT EXISTS defender_event_detail(
		id INTEGER PRIMARY KEY AUTOINCREMENT
		, time DATETIME DEFAULT (datetime(CURRENT_TIMESTAMP, 'localtime'))
		, event_id TEXT NOT NULL
		, event_type INTEGER NOT NULL
		, event_name TEXT NOT NULL
		, process_id INTEGER
		, process_name TEXT NOT NULL
		, process_path TEXT
		, process_commandline TEXT
		, target TEXT
		, rule_group_name TEXT
		, rule_name TEXT
		);
	CREATE INDEX IF NOT EXISTS index_defender_event_detail_time ON defender_event_detail (time);
)";
//******************************************************************************
static const char* sql_Cleanup = R"(
	DELETE FROM defender_event WHERE id IN (
	SELECT id FROM defender_event
	ORDER BY id DESC LIMIT ( SELECT COUNT(*) FROM defender_event ) OFFSET 10000);

	DELETE FROM defender_event_detail WHERE id IN (
	SELECT id FROM defender_event_detail
	ORDER BY id DESC LIMIT ( SELECT COUNT(*) FROM defender_event_detail ) OFFSET 10000);
)";
//******************************************************************************
static const char* sql_Insert = R"(
	INSERT INTO defender_event
		(event_id, event_type, event_name, process_name, process_path, process_commandline, target, rule_group_name, rule_name)
	VALUES
		(?, ?, ?, ?, ?, ?, ? ,?, ?)
	ON CONFLICT (date, event_id) DO UPDATE
		SET count=count+1, update_time=datetime(CURRENT_TIMESTAMP, 'localtime');
)";

static const char* sql_InsertDetail = R"(
	INSERT INTO defender_event_detail
		(event_id, event_type, event_name, process_id, process_name, process_path, process_commandline, target, rule_group_name, rule_name)
	VALUES
		(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
)";
//******************************************************************************
cxDefenderDatabase::cxDefenderDatabase(void)
{
	auto path = g_Path->GetCurrentPath(_T("iDefender.db"));

	for (int i = 0; i < 2; i++) {
		m_Database.Open(path);

		if (!m_Database) {
			DeleteFile(path);
			continue;
		}

		if (!m_Database.Execute(sql_CreateTable)) {
			m_Database.Close();
			DeleteFile(path);
			continue;
		}

		m_InsertStatement = m_Database.Prepare(sql_Insert);
		m_InsertDetailStatement = m_Database.Prepare(sql_InsertDetail);

		Cleanup();

		break;
	}
}
//******************************************************************************
void cxDefenderDatabase::Insert(std::shared_ptr<cxDefenderEvent> Event)
{
	if (!m_Database)
		return;

	if (++m_InsertCount > kCleanupCount) {
		Cleanup();
		m_InsertCount = 0;
	}

	// TODO(保存进程对应的Hash、ICON、Version等信息)

	m_InsertStatement.Reset();
	m_InsertStatement
		<< Event->EventId
		<< Event->EventType
		<< Event->EventName
		<< Event->ProcessName
		<< Event->ProcessPath
		<< Event->ProcessCommandline
		<< Event->TargetPath
		<< Event->RuleGroup
		<< Event->RuleName;
	m_InsertStatement.Execute();

	m_InsertDetailStatement.Reset();
	m_InsertDetailStatement
		<< Event->EventId
		<< Event->EventType
		<< Event->EventName
		<< Event->ProcessId
		<< Event->ProcessName
		<< Event->ProcessPath
		<< Event->ProcessCommandline
		<< Event->TargetPath
		<< Event->RuleGroup
		<< Event->RuleName;
	m_InsertDetailStatement.Execute();
}
//******************************************************************************
void cxDefenderDatabase::Cleanup(void)
{
	if (!m_Database)
		return;

	m_Database.Execute(sql_Cleanup);
}
//******************************************************************************
