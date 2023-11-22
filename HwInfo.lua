--
-- Main Premake5 file for building HwInfo project.
-- Copyright (c) 2020-2023 by Danil (Kenny) Dukhovenko, All rights reserved.
--
-- Requirement:
--  - ForceEngine.lua
--

-- HwInfo C++ Project
project "HwInfo"
	kind          "StaticLib"
	language      "C++"
	staticruntime "on"
	targetdir     ("%{ForceDir.BinLib}/" .. BuildDir .. "/%{prj.name}/lib")
	objdir        ("%{ForceDir.BinLib}/" .. BuildDir .. "/%{prj.name}/obj")
	
	files {
		"include/hwinfo/**.h",
		"include/hwinfo/utils/**.h",
		"src/init.cpp",
		"src/battery.cpp",
		"src/cpu.cpp",
		"src/disk.cpp",
		"src/gpu.cpp",
		"src/mainboard.cpp",
		"src/os.cpp",
		"src/ram.cpp",
		"src/system.cpp"
	}

	includedirs {
		"include"
	}

	filter "system:windows"
		systemversion "latest"

		files {
			"src/windows/utils/filesystem.cpp",
			"src/windows/battery.cpp",
			"src/windows/cpu.cpp",
			"src/windows/disk.cpp",
			"src/windows/gpu.cpp",
			"src/windows/mainboard.cpp",
			"src/windows/os.cpp",
			"src/windows/ram.cpp",
			"src/windows/WMIwrapper.cpp"
		}

		defines  {
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		files {
			"src/linux/utils/filesystem.cpp",
			"src/linux/battery.cpp",
			"src/linux/cpu.cpp",
			"src/linux/disk.cpp",
			"src/linux/gpu.cpp",
			"src/linux/mainboard.cpp",
			"src/linux/os.cpp",
			"src/linux/ram.cpp"
		}

	filter "system:macosx"
		files {
			"src/apple/utils/filesystem.cpp",
			"src/apple/battery.cpp",
			"src/apple/cpu.cpp",
			"src/apple/disk.cpp",
			"src/apple/gpu.cpp",
			"src/apple/mainboard.cpp",
			"src/apple/os.cpp",
			"src/apple/ram.cpp"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"