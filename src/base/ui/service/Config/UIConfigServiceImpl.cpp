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
#include "UIConfigServiceImpl.h"
//******************************************************************************
#define DEFAULT_CONFIG_SECTION _T("default")
//******************************************************************************
bool UIConfigServiceImplBase::SetSectionInt(const char* section, const char* entry, int data)
{
	m_settings->setValue(GetKeyName(section, entry), data);

	return true;
}
//******************************************************************************
bool UIConfigServiceImplBase::SetSectionString(const char* section, const char* entry, const char* data)
{
	m_settings->setValue(GetKeyName(section, entry), QStringFrom(data));

	return true;
}
//******************************************************************************
bool UIConfigServiceImplBase::SetSectionBinary(const char* section, const char* entry, void* data, int length)
{
	QByteArray arr((const char*)data, length);

	m_settings->setValue(GetKeyName(section, entry), arr);

	return true;
}
//******************************************************************************
bool UIConfigServiceImplBase::SetSectionByteArray(const char* section, const char* entry, const QByteArray& bytes)
{
	return SetSectionBinary(section, entry, (void*)bytes.data(), bytes.size());
}
//******************************************************************************
int UIConfigServiceImplBase::GetSectionInt(const char* section, const char* entry, int default_value)
{
	QVariant var = m_settings->value(GetKeyName(section, entry));

	bool ok = false;
	int data = var.toInt(&ok);

	return ok ? data : default_value;
}
//******************************************************************************
std::string UIConfigServiceImplBase::GetSectionString(const char* section, const char* entry, const char* default_value)
{
	QVariant var = m_settings->value(GetKeyName(section, entry));

	QString data = var.toString();

	if (data.isEmpty())
		return default_value;

	return data.toStdString();
}
//******************************************************************************
std::string UIConfigServiceImplBase::GetSectionBinary(const char* section, const char* entry)
{
	return GetSectionByteArray(section, entry).toStdString();
}
//******************************************************************************
QByteArray UIConfigServiceImplBase::GetSectionByteArray(const char* section, const char* entry)
{
	QVariant var = m_settings->value(GetKeyName(section, entry));

	return var.toByteArray();
}
//******************************************************************************
QString UIConfigServiceImplBase::GetKeyName(const char* section, const char* entry)
{
	QString str = section;

	if (!str.isEmpty())
		str += "/";

	str += entry;

	return str;
}
//******************************************************************************
