-- Workspace

workspace "Kadaver"
	language "C++"
	configurations {
		"Debug",
		"Release",
	}
	platforms {
		"Win32",
		"x64",
	}

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

	rtti "Off"

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Debug"}
		optimize "Full"

	filter {}

-- Demo application

project "Demo"
	kind "ConsoleApp"
	targetdir "../bin"
	objdir "../build"
	files {
		"demo/**.h",
		"demo/**.cpp",
	}
	includedirs {
		"demo",
		"engine/libCore",
	}
	libdirs {
		"../bin",
	}
	links {
		"libCore",
	}

	rtti "Off"

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Debug"}
		optimize "Full"
