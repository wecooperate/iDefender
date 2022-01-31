//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __stdafx_H__
#define __stdafx_H__
//******************************************************************************
#include <base/stdafx.h>
#include <spdlog\spdlog.h>
//******************************************************************************
template<>
struct fmt::formatter<CString>
{
	auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
	{
		return ctx.begin();
	}

	template<typename FormatContext>
	auto format(const CString& str, FormatContext& ctx) -> decltype(ctx.out())
	{
		return format_to(ctx.out(), "{}", (const char*)CT2A(str, CP_UTF8));
	}
};
//******************************************************************************
#endif
