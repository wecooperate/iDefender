//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIRecordEventModel_FBE55D4E_974B_4E69_A8B4_8DDE44E2FD99__
#define __UIRecordEventModel_FBE55D4E_974B_4E69_A8B4_8DDE44E2FD99__
//******************************************************************************
#include <QtSql/QSqlQueryModel>
#include <QDate>
//******************************************************************************
enum emMSGGroup {
	emMSGGroupInternal,
	emMSGGroupProcess,
	emMSGGroupFile,
	emMSGGroupRegistry,
	emMSGGroupNetwork,
	emMSGGroupMax,
};
//******************************************************************************
enum emRecordEventIndex {
	emRecordEventIndexProcessPath,
	emRecordEventIndexProcessCommandline,
	emRecordEventIndexEventType,
	emRecordEventIndexTime,
	emRecordEventIndexRuleName,
	emRecordEventIndexCount,
	emRecordEventIndexProcessName,
	emRecordEventIndexEventName,
	emRecordEventIndexTarget,
};
//******************************************************************************
class UIRecordEventModel : public QSqlQueryModel
{
	Q_OBJECT

public:
	UIRecordEventModel(QObject* parent = nullptr);

public:
	void SetQuery(QDate* date, bool detail);

protected:
	QVariant data(const QModelIndex& item, int role = Qt::DisplayRole) const override;

protected:
	QIcon GetPathIcon(const QString& Path) const;
	QIcon GetTypeIcon(uint32_t Type) const;

protected:
	QIcon m_TypeIcons[emMSGGroupMax];
	mutable std::map<QString, QIcon> m_PathIcons;
};
//******************************************************************************
#endif
