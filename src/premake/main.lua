require "customizations"

-- Workspace

workspace "Kadaver"
	language "C++"
	location ".."
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

project "KadaverCore"
	kind "SharedLib"
	location ".."
	targetdir "../../bin"
	objdir "../../build"
	defines {
		"LIB_CORE",
	}
	files {
		"../engine/libCore/**.h",
		"../engine/libCore/**.cpp",
	}
	includedirs {
		"../engine/libCore",
	}

	-- Per-toolset settings

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
		cppdialect "C++14"
		rtti "Off"

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

	-- Per-toolset settings

	filter {"toolset:clang or gcc"}
		buildoptions {
			"-g",
		}

	-- Per-configuration settings

	filter {"configurations:Debug"}
		optimize "Off"

	filter {"configurations:Release"}
		optimize "Full"

	filter {}
		cppdialect "C++14"
		rtti "Off"
