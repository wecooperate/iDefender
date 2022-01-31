//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __Hash_F73A0A18_FFBE_4352_B18D_909F1B9A287A__
#define __Hash_F73A0A18_FFBE_4352_B18D_909F1B9A287A__
//******************************************************************************
#include "mbedtls_mini/md5.h"
//******************************************************************************
template<int LENGHT>
struct cxHashValue
{
	static constexpr auto length = LENGHT;

	unsigned char value[length];

	CString ToString(void)
	{
		CString str;
		str.Preallocate(length * 2 + 1);

		for (int i = 0; i < length; i++) {
			str.AppendFormat(_T("%02X"), value[i]);
		}

		return str;
	}
};
//******************************************************************************
class cxHashMD5 : public mbedtls_md5_context
{
public:
	using HashValue = cxHashValue<16>;

public:
	cxHashMD5(void);

public:
	void Update(const unsigned char* data, size_t length);
	HashValue Finish(void);
};
//******************************************************************************
#endif
