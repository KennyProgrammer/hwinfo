// Copyright (c) Leon Freist <freist@informatik.uni-freiburg.de>
// This software is part of HWBenchmark

#include "hwinfo/platform.h"

#ifdef HWINFO_WINDOWS

#include <string>

#include "hwinfo/WMIwrapper.h"
#include "hwinfo/mainboard.h"

namespace hwinfo {

// _____________________________________________________________________________________________________________________
std::string MainBoard::getVendor() {
  std::vector<const wchar_t*> manufacturer{};
  wmi::queryWMI("Win32_BaseBoard", "Manufacturer", manufacturer);
  if (manufacturer.empty())
	  return "<unknown>";
  auto ret = manufacturer[0];
  std::wstring tmp(ret);
  return {tmp.begin(), tmp.end()};
}

// _____________________________________________________________________________________________________________________
std::string MainBoard::getName() {
  std::vector<const wchar_t*> name{};
  wmi::queryWMI("Win32_BaseBoard", "Product", name);
  if (name.empty())
	  return "<unknown>";
  auto ret = name[0];
  std::wstring tmp(ret);
  return {tmp.begin(), tmp.end()};
}

// _____________________________________________________________________________________________________________________
std::string MainBoard::getVersion() {
  std::vector<const wchar_t*> version{};
  wmi::queryWMI("Win32_BaseBoard", "Version", version);
  if (version.empty())
	  return "<unknown>";
  auto ret = version[0];
  std::wstring tmp(ret);
  return {tmp.begin(), tmp.end()};
}

// _____________________________________________________________________________________________________________________
std::string MainBoard::getSerialNumber() {
  std::vector<const wchar_t*> serialNumber{};
  wmi::queryWMI("Win32_BaseBoard", "SerialNumber", serialNumber);
  if (serialNumber.empty())
	  return "<unknown>";
  auto ret = serialNumber[0];
  std::wstring tmp(ret);
  return {tmp.begin(), tmp.end()};
}

}  // namespace hwinfo

#endif  // HWINFO_WINDOWS
