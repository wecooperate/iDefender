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
#include "Hash.h"
#include "mbedtls_mini/md5.c"
//******************************************************************************
cxHashMD5::cxHashMD5(void)
{
	mbedtls_md5_init(this);
	mbedtls_md5_starts(this);
}
//******************************************************************************
void cxHashMD5::Update(const unsigned char* data, size_t length)
{
	mbedtls_md5_update(this, data, length);
}
//******************************************************************************
cxHashMD5::HashValue cxHashMD5::Finish(void)
{
	HashValue hash;
	mbedtls_md5_finish(this, hash.value);
	return hash;
}
//******************************************************************************
