// Copyright Leon Freist
// Author Leon Freist <freist@informatik.uni-freiburg.de>

#include "hwinfo/platform.h"

#ifdef HWINFO_WINDOWS

#include "hwinfo/WMIwrapper.h"
#include "hwinfo/disk.h"
#include "hwinfo/utils/stringutils.h"

#include <iostream>

namespace hwinfo {

// _____________________________________________________________________________________________________________________
std::vector<Disk> getAllDisks() {
  std::vector<Disk> disks;
  std::vector<const wchar_t*> res{};
  wmi::queryWMI("Win32_DiskDrive", "Manufacturer", res);
  if (res.empty() || res.front() == nullptr) {
    return {};
  }
  for (const auto& v : res) {
    disks.push_back(Disk());
    disks.back()._vendor = wstring_to_std_string(v);
  }
  std::cout << "mark 3\n" << std::flush;
  res.clear();
  wmi::queryWMI("Win32_DiskDrive", "Model", res);
  for (int i = 0; i < res.size(); ++i) {
    if (i >= disks.size()) {
      break;
    }
    disks[i]._model = wstring_to_std_string(res[i]);
  }
  std::cout << "mark 4\n" << std::flush;
  res.clear();
  wmi::queryWMI("Win32_DiskDrive", "SerialNumber", res);
  std::cout << disks.size() << " " << res.size() << std::endl;
  for (int i = 0; i < res.size(); ++i) {
    if (i >= disks.size()) {
      break;
    }
    std::cout << i << std::endl;
    std::cout << res[i] << std::endl;
    std::wstring tmp(res[i]);
    std::cout << wstring_to_std_string(tmp) << std::endl;
    disks[i]._serialNumber = wstring_to_std_string(res[i]);
  }
  std::cout << "mark 5\n" << std::flush;
  std::vector<const wchar_t*> sizes;
  // it will return L"Size" Str
  wmi::queryWMI("Win32_DiskDrive", "Size", sizes);
  for (int i = 0; i < res.size(); ++i) {
    if (i >= disks.size()) {
      break;
    }
    disks[i]._size_Bytes = std::stoll(wstring_to_std_string(sizes[i]));
  }
  std::cout << "mark 6\n" << std::flush;
  return disks;
}

}  // namespace hwinfo

#endif  // HWINFO_WINDOWS