//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIConfigService_48A5A32C_7B78_4357_BCA7_8194C2309B50__
#define __UIConfigService_48A5A32C_7B78_4357_BCA7_8194C2309B50__
//******************************************************************************
#include "UIService.h"
//******************************************************************************
interface UIConfigService : public UIService
{
	static constexpr auto NAME = "config";

public:
	virtual bool SetSectionInt(const char* section, const char* entry, int data) = 0;
	virtual bool SetSectionString(const char* section, const char* entry, const char* data) = 0;
	virtual bool SetSectionBinary(const char* section, const char* entry, void* data, int length) = 0;
	virtual int GetSectionInt(const char* section, const char* entry, int default_value = 0) = 0;
	virtual std::string GetSectionString(const char* section, const char* entry, const char* default_value = "") = 0;
	virtual std::string GetSectionBinary(const char* section, const char* entry) = 0;
	virtual QByteArray GetSectionByteArray(const char* section, const char* entry) = 0;
	virtual bool SetSectionByteArray(const char* section, const char* entry, const QByteArray& bytes) = 0;

public:
	template<typename T>
	inline void SaveState(T * wnd, const char* name)
	{
		SetSectionByteArray(name, "state", wnd->saveState());
	}

	template<typename T>
	inline void LoadState(T * wnd, const char* name)
	{
		wnd->restoreState(GetSectionByteArray(name, "state"));
	}

	template<typename T>
	inline void SaveGeometry(T * wnd, const char* name)
	{
		SetSectionByteArray(name, "geometry", wnd->saveGeometry());
	}

	template<typename T>
	inline void LoadGeometry(T * wnd, const char* name)
	{
		wnd->restoreGeometry(GetSectionByteArray(name, "geometry"));
	}
};
//******************************************************************************
#endif
