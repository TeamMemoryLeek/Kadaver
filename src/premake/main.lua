require "customizations"

-- Workspace

workspace "Kadaver"
	language "C++"
	location ".."
	configurations {
		"Debug",
		"Release",
	}

	if (_LINUX_REMOTE) then
		toolset "gcc"
		system "linux"
		platforms {
			"x86",
			"x64",
			"ARM",
		}
	elseif (_ACTION_VS) then
		toolset "msc"
		platforms {
			"Win32",
			"x64",
		}
	end

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
			"-fPIC",
			"-g",
		}
		links {
			"pthread",
			"asound",
		}

	-- Per-system settings

	filter {"system:linux"}
		links {
			"X11",
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

	-- Remote linux settings

	if (_LINUX_REMOTE) then
		objdir "../build"
		remoteprojectrootdir("$(RemoteRootDir)/$(ProjectName)/Kadaver/Core/")
		targetdir "../bin"
		buildoptions {
			"-I $(RemoteRootDir)/KadaverCore",
		}
	else
		objdir "../../build"
		targetdir "../../bin"
	end

-- Demo application

project "Demo"
	dependson "KadaverCore"
	kind "ConsoleApp"
	location ".."
	
	files {
		"../demo/**.h",
		"../demo/**.cpp",
		"../demo/**.hpp",
	}
	includedirs {
		"../demo",
		"../engine",
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

	filter {"system:linux"}
		links {
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

	-- Remote linux settings

	if (_LINUX_REMOTE) then
		debugdir "$(RemoteProjectDir)"
		objdir "$(ProjectDir)build"
		remoteprojectrootdir("$(RemoteRootDir)/$(ProjectName)")
		targetdir "$(ProjectDir)bin/$(Platform)/$(Configuration)"
		targetextension ".out"
		absolutelinks {
			"$(RemoteRootDir)/KadaverCore/Kadaver/Core/bin/libKadaverCore.so",
		}
		buildoptions {
			"-Wl,-rpath=.",
			"-I $(RemoteRootDir)/Demo",
			"-I $(RemoteRootDir)/KadaverCore",
		}
		flags {
			"RelativeLinks",
		}
	else
		debugdir "$(OutDir)"
		objdir "../../build"
		targetdir "../../bin"
		libdirs {
			"../../bin",
		}
		links {
			"KadaverCore",
		}
	end
