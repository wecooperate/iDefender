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
#include "UIRecordEventModel.h"
#include <QtSql/QSqlRecord>
//******************************************************************************
UIRecordEventModel::UIRecordEventModel(QObject* parent)
	: QSqlQueryModel(parent)
{
	m_TypeIcons[emMSGGroupProcess] = g_res->icon_msg_process;
	m_TypeIcons[emMSGGroupFile] = g_res->icon_msg_file;
	m_TypeIcons[emMSGGroupRegistry] = g_res->icon_msg_registry;
	m_TypeIcons[emMSGGroupNetwork] = g_res->icon_msg_network;
}
//******************************************************************************
void UIRecordEventModel::SetQuery(QDate* date, bool detail)
{
	QString query;

	if (detail) {
		query = "SELECT process_path, process_commandline, event_type, time, rule_name, 1 as count, process_name, event_name, target FROM defender_event_detail";
	} else {
		query = "SELECT process_path, process_commandline, event_type, update_time as time, rule_name, count, process_name, event_name, target FROM defender_event";
	}

	if (date) {
		QString date_str = date->toString("yyyy-MM-dd");
		auto next_date = date->addDays(1);
		QString next_date_str = next_date.toString("yyyy-MM-dd");
		query += QString(" where time >= '%1' and time < '%2'").arg(date_str).arg(next_date_str);
	}

	query += " ORDER BY time DESC;";

	setQuery(query);

	setHeaderData(emRecordEventIndexTime, Qt::Horizontal, detail ? tr("Time") : tr("LastTime"));
	setHeaderData(emRecordEventIndexRuleName, Qt::Horizontal, tr("RuleName"));
	setHeaderData(emRecordEventIndexCount, Qt::Horizontal, tr("Count"));
	setHeaderData(emRecordEventIndexProcessName, Qt::Horizontal, tr("ProcessName"));
	setHeaderData(emRecordEventIndexEventName, Qt::Horizontal, tr("EventName"));
	setHeaderData(emRecordEventIndexTarget, Qt::Horizontal, tr("Target"));
}
//******************************************************************************
QVariant UIRecordEventModel::data(const QModelIndex& item, int role) const
{
	QVariant value = __super::data(item, role);

	if (!item.isValid())
		return value;

	auto column = item.column();
	auto row = item.row();

	if (role == Qt::DecorationRole) {
		switch (column) {
		case emRecordEventIndexProcessName:
			return GetPathIcon(__super::data(index(row, emRecordEventIndexProcessPath)).toString());

		case emRecordEventIndexEventName + 1:
			return GetTypeIcon(__super::data(index(row, emRecordEventIndexEventType)).toUInt());

		default:
			break;
		}
	} else if (role == Qt::ToolTipRole) {
		switch (column) {
		case emRecordEventIndexProcessName:
			return QString("Path : %1\nCommandline : %2")
				.arg(__super::data(index(row, emRecordEventIndexProcessPath)).toString())
				.arg(__super::data(index(row, emRecordEventIndexProcessCommandline)).toString());

		default:
			break;
		}
	}

	return value;
}
//******************************************************************************
QIcon UIRecordEventModel::GetPathIcon(const QString& Path) const
{
	if (auto it = m_PathIcons.find(Path); it != m_PathIcons.end()) {
		return it->second;
	}

	SHFILEINFO sfi = {};
	SHGetFileInfo(QStringToCString(Path), NULL, &sfi, sizeof(sfi), SHGFI_ICON);
	auto icon = sfi.hIcon ? sfi.hIcon : LoadIcon(NULL, IDI_APPLICATION);
	QIcon result = QtWin::fromHICON(icon);
	DestroyIcon(icon);

	m_PathIcons.insert(std::make_pair(Path, result));

	return result;
}
//******************************************************************************
QIcon UIRecordEventModel::GetTypeIcon(uint32_t Type) const
{
	auto index = Type / 100;

	return index > emMSGGroupMax ? QIcon() : m_TypeIcons[index];
}
//******************************************************************************
