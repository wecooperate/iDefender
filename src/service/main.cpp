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
#include "ServiceMain.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
//******************************************************************************
int _tmain(int argc, LPTSTR argv[])
{
	auto max_size = 10 * 1024 * 1024;
	auto max_files = 2;
	auto logger = spdlog::rotating_logger_mt("main",
		(const char*)CW2A(g_Path->GetCurrentPath(_T("iDefenderService.log"))),
		max_size,
		max_files);
	spdlog::set_default_logger(logger);
	spdlog::set_level(spdlog::level::debug);
	spdlog::flush_every(std::chrono::seconds(2));

	return g_ServiceMain->WinMain(argc, argv);
}
//******************************************************************************
