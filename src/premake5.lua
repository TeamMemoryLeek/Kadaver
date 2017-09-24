-- Workspace

workspace "Kadaver"
	language "C++"
	configurations {
		"Debug",
		"Release",
	}

	-- Visual Studio

	if _ACTION:match("vs*") then
		platforms {
			"Win32",
			"x64",
		}
	end

-- Core library

project "libCore"
	kind "SharedLib"
	targetdir "../bin"
	objdir "../build"
	defines {
		"LIB_CORE",
	}
	files {
		"engine/libCore/**.h",
		"engine/libCore/**.cpp",
	}
	includedirs {
		"engine/libCore",
	}

	-- Per-configuration settings

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Debug"}
		optimize "Full"

	filter {}
		cppdialect "C++14"
		rtti "Off"

-- Demo application

project "Demo"
	dependson "libCore"
	kind "ConsoleApp"
	targetdir "../bin"
	objdir "../build"
	files {
		"demo/**.h",
		"demo/**.cpp",
	}
	includedirs {
		"demo",
		"engine",
	}
	libdirs {
		"../bin",
	}
	links {
		"libCore",
	}

	-- Per-configuration settings

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Debug"}
		optimize "Full"

	filter {}
		cppdialect "C++14"
		rtti "Off"
