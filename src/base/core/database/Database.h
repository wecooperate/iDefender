//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.

  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.

  For other usage or business cooperation, please contact admin@iMonitorSDK.com

--*/
//******************************************************************************
#ifndef Database_H
#define Database_H
//******************************************************************************
#include <sqlite/sqlite3.h>
//******************************************************************************
// clang-format off
//******************************************************************************
class cxDatabaseBlob
{
public:
	cxDatabaseBlob(const char* Value, int Length)
		: m_Value(Value)
		, m_Length(Length)
	{}

public:
	const void*	m_Value;
	int			m_Length;
};
//******************************************************************************
class BASE_API cxDatabaseStatement : public cxSafeObject
{
	enum { emFirstBinder = 1 };

public:
	cxDatabaseStatement					(sqlite3_stmt* Statement = NULL);
	~cxDatabaseStatement				(void);

public:
	cxDatabaseStatement					(cxDatabaseStatement&& Target);
	cxDatabaseStatement& operator =		(cxDatabaseStatement&& Target);

public:
	operator		bool				(void);
	operator		sqlite3_stmt*		(void);
	sqlite3_stmt**	operator&			(void);

public:
	bool			BindNull			(int Index);
	bool			BindInt				(int Index, int Value);
	bool			BindDouble			(int Index, double Value);
	bool			BindInt32			(int Index, uint32_t Value);
	bool			BindInt64			(int Index, uint64_t Value);
	bool			BindText			(int Index, const char*	Value, bool Transient = true);
	bool			BindBlob			(int Index, const void* Value, int Length, bool Transient = true);

	bool			Bind				(int Index, int Value);
	bool			Bind				(int Index, double Value);
	bool			Bind				(int Index, uint32_t Value);
	bool			Bind				(int Index, uint64_t Value);
	bool			Bind				(int Index, const char*	Value, bool Transient = true);
	bool			Bind				(int Index, const CString& Value, bool Transient = true);
	bool			Bind				(int Index, const void*	Value, int Length, bool Transient = true);
	bool			Bind				(int Index, const cxDatabaseBlob& Value, bool Transient = true);

public:
	inline bool		Bind				(int Index, ULONG Value) { return Bind(Index, (uint32_t)Value); }

	template<typename T>
	inline cxDatabaseStatement& operator << (const T& Value)
	{
		Bind(m_BindIndex++, Value);
		return *this;
	}

public:
	int				GetColumnCount		(void);
	int				GetLength			(int Index);

public:
	int				GetInt				(int Index);
	double			GetDouble			(int Index);
	uint32_t		GetInt32			(int Index);
	uint64_t		GetInt64			(int Index);
	const char*		GetText				(int Index);
	const void*		GetBlob				(int Index, int& Length);
	CString			GetString			(int Index);

public:
	bool			Execute				(void);
	bool			Query				(void);

public:
	bool			Reset				(void);
	bool			Close				(void);

private:
	sqlite3_stmt*	m_Statement;
	int				m_BindIndex;
};
//******************************************************************************
class BASE_API cxDatabase : public cxSafeObject
{
public:
	cxDatabase							(void);
	~cxDatabase							(void);

	operator		bool				(void);

public:
	bool			Open				(const char* DBName);
	bool			Open				(const wchar_t* DBName);
	bool			Close				(void);

public:
	const char*		ErrorMessage		(void);

public:
	bool			Execute				(const char* lpSql);
	bool			Prepare				(const char* lpSql, sqlite3_stmt** ppStmt);
	bool			Prepare				(const char* lpSql, cxDatabaseStatement* dbStatement);
	cxDatabaseStatement Prepare			(const char* lpSql);

public:
	bool			TransactionBegin	(void);
	bool			TransactionRollback	(void);
	bool			TransactionCommit	(void);

public:
	int				GetLastInsertRowId	(void);

protected:
	sqlite3*		m_Database;
};
//******************************************************************************
#endif
