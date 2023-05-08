// Copyright Leon Freist
// Author Leon Freist <freist@informatik.uni-freiburg.de>

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)

#pragma once

#include <WbemIdl.h>
#include <Windows.h>
#include <comdef.h>
#include <ntddscsi.h>

#include <string>
#include <type_traits>
#include <vector>
#pragma comment(lib, "wbemuuid.lib")

namespace hwinfo {
namespace wmi {

bool initializeCOMLibrary();
bool closeCOMLibrary();

bool queryWMI(const std::string& WMIClass, std::string field, std::vector<wchar_t*>& value, const std::string& serverName = "ROOT\\CIMV2");
bool queryWMI(const std::string& WMIClass, std::string field, std::vector<const wchar_t*>& value, const std::string& serverName = "ROOT\\CIMV2");
bool queryWMI(const std::string& WMIClass, std::string field, std::vector<unsigned long long>& value, const std::string& serverName = "ROOT\\CIMV2");
bool queryWMI(const std::string& WMIClass, std::string field, std::vector<long long>& value, const std::string& serverName = "ROOT\\CIMV2");
bool queryWMI(const std::string& WMIClass, std::string field, std::vector<int>& value, const std::string& serverName = "ROOT\\CIMV2");

}  // namespace wmi
}  // namespace hwinfo

#endif
