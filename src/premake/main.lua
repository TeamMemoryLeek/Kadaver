require "customizations"

-- Workspace

workspace "Kadaver"
	language "C++"
	location ".."
	configurations {
		"Debug",
		"Release",
	}

	-- Per-action settings

	filter {"action:vs*"}
		toolset "msc"
		platforms {
			"Win32",
			"x64",
		}

-- Core library

project "KadaverCore"
	kind "SharedLib"
	location ".."
	targetdir "../../bin"
	objdir "../../build"
	defines {
		"LIB_CORE",
	}
	files {
		"../engine/Kadaver/Core/**.h",
		"../engine/Kadaver/Core/**.cpp",
	}
	includedirs {
		"../engine",
	}

	-- Per-action settings

	filter {"action:xcode4"}
		xcodebuildsettings
		{
			["CLANG_CXX_LANGUAGE_STANDARD"] = "c++14";
		}

	filter {"action:not xcode4"}
		cppdialect "C++14"

	-- Per-toolset settings

	filter {"toolset:msc"}
		disablewarnings {
			-- "STL class needs dll-interface"
			"4251",
		}
		links{
			"dsound.lib",
			"dxguid.lib",
			"winmm.lib",
		}

	filter {"toolset:clang or gcc"}
		buildoptions {
			"-g",
		}
		links {
			"pthread",
		}

	-- Per-configuration settings

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Release"}
		optimize "Full"

	filter {}
		rtti "Off"
		warnings "Extra"

-- Demo application

project "Demo"
	dependson "KadaverCore"
	kind "ConsoleApp"
	location ".."
	targetdir "../../bin"
	objdir "../../build"
	files {
		"../demo/**.h",
		"../demo/**.cpp",
	}
	includedirs {
		"../demo",
		"../engine",
	}
	libdirs {
		"../../bin",
	}
	links {
		"KadaverCore",
	}

	-- Per-action settings

	filter {"action:xcode4"}
		sysincludedirs {
			"../engine",
		}
		xcodebuildsettings
		{
			["CLANG_CXX_LANGUAGE_STANDARD"] = "c++14";
		}

	filter {"action:not xcode4"}
		cppdialect "C++14"

	-- Per-toolset settings

	filter {"toolset:msc"}
		disablewarnings {
			-- "STL class needs dll-interface"
			"4251",
		}

	filter {"toolset:clang or gcc"}
		buildoptions {
			"-g",
		}
		links {
			"pthread",
		}

	-- Per-configuration settings

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Release"}
		optimize "Full"

	filter {}
		rtti "Off"
		warnings "Extra"
