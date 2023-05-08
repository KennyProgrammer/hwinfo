// Copyright Leon Freist & Danil Dukhovenko
// Author Leon Freist <freist@informatik.uni-freiburg.de>

#include "hwinfo/platform.h"

#ifdef HWINFO_WINDOWS

#include <string>
#include <vector>

#if defined(unix) || defined(__unix) || defined(__unix__)
#include "hwinfo/utils/subprocess.h"
#elif defined(__APPLE__)
#elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include "hwinfo/WMIwrapper.h"
#pragma comment(lib, "wbemuuid.lib")
#endif

#include "hwinfo/init.h"

namespace hwinfo {

	bool HwInfo::init() {
		return hwinfo::wmi::initializeCOMLibrary();
	}

	bool HwInfo::close() {
		return hwinfo::wmi::closeCOMLibrary();
	}
}

#endif
