//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.

  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.

  For other usage or business cooperation, please contact admin@iMonitorSDK.com

--*/
//******************************************************************************
#include "stdafx.h"
#include "Database.h"
//******************************************************************************
cxDatabaseStatement::cxDatabaseStatement(sqlite3_stmt* Statement)
	: m_Statement(Statement)
	, m_BindIndex(emFirstBinder)
{
}
//******************************************************************************
cxDatabaseStatement::~cxDatabaseStatement(void)
{
	Close();
}
//******************************************************************************
cxDatabaseStatement::cxDatabaseStatement(cxDatabaseStatement&& Target)
{
	m_Statement = Target.m_Statement;
	m_BindIndex = Target.m_BindIndex;

	Target.m_Statement = NULL;
}
//******************************************************************************
cxDatabaseStatement& cxDatabaseStatement::operator=(cxDatabaseStatement&& Target)
{
	Close();

	m_Statement = Target.m_Statement;
	m_BindIndex = Target.m_BindIndex;

	Target.m_Statement = NULL;

	return *this;
}
//******************************************************************************
cxDatabaseStatement::operator bool(void)
{
	return m_Statement != NULL;
}
//******************************************************************************
cxDatabaseStatement::operator sqlite3_stmt*()
{
	return m_Statement;
}
//******************************************************************************
sqlite3_stmt** cxDatabaseStatement::operator&()
{
	return &m_Statement;
}
//******************************************************************************
bool cxDatabaseStatement::BindNull(int Index)
{
	return SQLITE_OK == sqlite3_bind_null(m_Statement, Index);
}
//******************************************************************************
bool cxDatabaseStatement::BindInt(int Index, int Value)
{
	return SQLITE_OK == sqlite3_bind_int(m_Statement, Index, Value);
}
//******************************************************************************
bool cxDatabaseStatement::BindDouble(int Index, double Value)
{
	return SQLITE_OK == sqlite3_bind_double(m_Statement, Index, Value);
}
//******************************************************************************
bool cxDatabaseStatement::BindInt32(int Index, uint32_t Value)
{
	return SQLITE_OK == sqlite3_bind_int(m_Statement, Index, (int)Value);
}
//******************************************************************************
bool cxDatabaseStatement::BindInt64(int Index, uint64_t Value)
{
	return SQLITE_OK == sqlite3_bind_int64(m_Statement, Index, (sqlite3_int64)Value);
}
//******************************************************************************
bool cxDatabaseStatement::BindText(int Index, const char* Value, bool Transient)
{
	return SQLITE_OK == sqlite3_bind_text(m_Statement, Index, Value, (int)strlen(Value), Transient ? SQLITE_TRANSIENT : SQLITE_STATIC);
}
//******************************************************************************
bool cxDatabaseStatement::BindBlob(int Index, const void* Value, int Length, bool Transient)
{
	return SQLITE_OK == sqlite3_bind_blob(m_Statement, Index, Value, Length, Transient ? SQLITE_TRANSIENT : SQLITE_STATIC);
}
//******************************************************************************
bool cxDatabaseStatement::Bind(int Index, int Value)
{
	return SQLITE_OK == sqlite3_bind_int(m_Statement, Index, Value);
}
//******************************************************************************
bool cxDatabaseStatement::Bind(int Index, double Value)
{
	return SQLITE_OK == sqlite3_bind_double(m_Statement, Index, Value);
}
//******************************************************************************
bool cxDatabaseStatement::Bind(int Index, uint32_t Value)
{
	return SQLITE_OK == sqlite3_bind_int(m_Statement, Index, (int)Value);
}
//******************************************************************************
bool cxDatabaseStatement::Bind(int Index, uint64_t Value)
{
	return SQLITE_OK == sqlite3_bind_int64(m_Statement, Index, (sqlite3_int64)Value);
}
//******************************************************************************
bool cxDatabaseStatement::Bind(int Index, const char* Value, bool Transient)
{
	return SQLITE_OK == sqlite3_bind_text(m_Statement, Index, Value, (int)strlen(Value), Transient ? SQLITE_TRANSIENT : SQLITE_STATIC);
}
//******************************************************************************
bool cxDatabaseStatement::Bind(int Index, const void* Value, int Length, bool Transient)
{
	return SQLITE_OK == sqlite3_bind_blob(m_Statement, Index, Value, Length, Transient ? SQLITE_TRANSIENT : SQLITE_STATIC);
}
//******************************************************************************
bool cxDatabaseStatement::Bind(int Index, const CString& Value, bool Transient)
{
	return Bind(Index, (const char*)CT2A(Value, CP_UTF8), true);
}
//******************************************************************************
bool cxDatabaseStatement::Bind(int Index, const cxDatabaseBlob& Value, bool Transient)
{
	return Bind(Index, Value.m_Value, Value.m_Length, Transient);
}
//******************************************************************************
bool cxDatabaseStatement::Execute(void)
{
	return SQLITE_DONE == sqlite3_step(m_Statement);
}
//******************************************************************************
bool cxDatabaseStatement::Query(void)
{
	return SQLITE_ROW == sqlite3_step(m_Statement);
}
//******************************************************************************
bool cxDatabaseStatement::Reset(void)
{
	m_BindIndex = emFirstBinder;

	return SQLITE_OK == sqlite3_reset(m_Statement);
}
//******************************************************************************
bool cxDatabaseStatement::Close(void)
{
	if (NULL == m_Statement)
		return true;

	if (SQLITE_OK == sqlite3_finalize(m_Statement)) {
		m_Statement = NULL;
		return true;
	}

	return false;
}
//******************************************************************************
int cxDatabaseStatement::GetColumnCount(void)
{
	return sqlite3_column_count(m_Statement);
}
//******************************************************************************
int cxDatabaseStatement::GetLength(int Index)
{
	return sqlite3_column_bytes(m_Statement, Index);
}
//******************************************************************************
uint32_t cxDatabaseStatement::GetInt32(int Index)
{
	return (uint32_t)sqlite3_column_int(m_Statement, Index);
}
//******************************************************************************
uint64_t cxDatabaseStatement::GetInt64(int Index)
{
	return (uint64_t)sqlite3_column_int64(m_Statement, Index);
}
//******************************************************************************
int cxDatabaseStatement::GetInt(int Index)
{
	return sqlite3_column_int(m_Statement, Index);
}
//******************************************************************************
double cxDatabaseStatement::GetDouble(int Index)
{
	return sqlite3_column_double(m_Statement, Index);
}
//******************************************************************************
const char* cxDatabaseStatement::GetText(int Index)
{
	return (const char*)sqlite3_column_text(m_Statement, Index);
}
//******************************************************************************
const void* cxDatabaseStatement::GetBlob(int Index, int& Length)
{
	Length = sqlite3_column_bytes(m_Statement, Index);

	return sqlite3_column_blob(m_Statement, Index);
}
//******************************************************************************
CString cxDatabaseStatement::GetString(int Index)
{
	return CString(GetText(Index));
}
//******************************************************************************
cxDatabase::cxDatabase()
{
	m_Database = NULL;
}
//******************************************************************************
cxDatabase::~cxDatabase()
{
	Close();
}
//******************************************************************************
cxDatabase::operator bool(void)
{
	return m_Database != NULL;
}
//******************************************************************************
bool cxDatabase::Open(const char* DBName)
{
	Close();

	return SQLITE_OK == sqlite3_open(DBName, &m_Database);
}
//******************************************************************************
bool cxDatabase::Open(const wchar_t* DBName)
{
	return Open((const char*)CW2A(DBName, CP_UTF8));
}
//******************************************************************************
bool cxDatabase::Close(void)
{
	bool ret = true;

	if (m_Database) {
		ret = (SQLITE_OK == sqlite3_close(m_Database));
		m_Database = NULL;
	}

	return ret;
}
//******************************************************************************
bool cxDatabase::Execute(const char* lpSql)
{
	if (!m_Database || !lpSql)
		return false;

	return SQLITE_OK == sqlite3_exec(m_Database, lpSql, NULL, NULL, NULL);
}
//******************************************************************************
bool cxDatabase::Prepare(const char* lpSql, sqlite3_stmt** ppStmt)
{
	if (!m_Database || !lpSql || !ppStmt)
		return false;

	return SQLITE_OK == sqlite3_prepare_v2(m_Database, lpSql, (int)strlen(lpSql), ppStmt, NULL);
}
//******************************************************************************
bool cxDatabase::Prepare(const char* lpSql, cxDatabaseStatement* dbStatement)
{
	if (!dbStatement)
		return false;

	dbStatement->Close();

	if (!m_Database || !lpSql)
		return false;

	return SQLITE_OK == sqlite3_prepare_v2(m_Database, lpSql, (int)strlen(lpSql), &*dbStatement, NULL);
}
//******************************************************************************
cxDatabaseStatement cxDatabase::Prepare(const char* lpSql)
{
	if (!m_Database || !lpSql)
		return cxDatabaseStatement();

	sqlite3_stmt* stmt = NULL;

	sqlite3_prepare_v2(m_Database, lpSql, (int)strlen(lpSql), &stmt, NULL);

	return cxDatabaseStatement(stmt);
}
//******************************************************************************
const char* cxDatabase::ErrorMessage(void)
{
	return sqlite3_errmsg(m_Database);
}
//******************************************************************************
bool cxDatabase::TransactionBegin(void)
{
	return Execute("begin transaction");
}
//******************************************************************************
bool cxDatabase::TransactionRollback(void)
{
	return Execute("rollback transaction");
}
//******************************************************************************
bool cxDatabase::TransactionCommit(void)
{
	return Execute("commit transaction");
}
//******************************************************************************
int cxDatabase::GetLastInsertRowId(void)
{
	return sqlite3_last_insert_rowid(m_Database);
}
//******************************************************************************
