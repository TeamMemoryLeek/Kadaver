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

	-- Per-configuration settings

	filter {"configurations:Debug"}
		defines {
			"DEBUG",
		}

	filter {"configurations:Release"}
		defines {
			"RELEASE",
			"NDEBUG",
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
		"../engine/Kadaver/Core/**.hpp",
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
			"asound",
		}

	-- Per-system settings

	filter {"system:windows"}
		links {
			"opengl32",
		}

	filter {"system:linux"}
		links {
			"GL",
		}

	filter {"system:macosx"}
		files {
			"../engine/Kadaver/Core/**.m",
			"../engine/Kadaver/Core/**.mm",
		}
		links {
			"Cocoa.framework",
		}

	filter {"system:not macosx"}
		removefiles {
			"../engine/Kadaver/Core/ObjC/**",
		}

	-- Per-configuration settings

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Release"}
		optimize "Full"

	-- Global settings

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
	debugdir "$(OutDir)"
	
	files {
		"../demo/**.h",
		"../demo/**.cpp",
		"../demo/**.hpp",
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
			"asound",
		}

	-- Per-system settings

	filter {"system:windows"}
		links {
			"opengl32",
		}

	filter {"system:linux"}
		links {
			"GL",
			"X11",
		}

	-- Per-configuration settings

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Release"}
		optimize "Full"

	-- Global settings

	filter {}
		rtti "Off"
		warnings "Extra"
