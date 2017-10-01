--
-- Helper functions
--

function arrayContains(array, value)
	for i, v in ipairs(array) do
		if v == value then
			return true
		end
	end

	return false
end

-- Global variables

_ACTION_VS = (_ACTION:match("vs*"))
_LINUX_REMOTE = (arrayContains(_ARGS, "remote=linux"))

--
-- Local variables
--

local p = premake


--
-- CodeLite customizations
--

if (_ACTION == 'codelite') then
	require 'codelite'

	local m = p.modules.codelite

	-- Modify linker library path

	p.override(m.project, 'environment', function(base, prj)
		_p(3, '<Environment EnvVarSetName="&lt;Use Defaults&gt;" DbgSetName="&lt;Use Defaults&gt;">')
		_x(4, '<![CDATA[%s]]>', 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH;'.._MAIN_SCRIPT_DIR..'/../../bin')
		_p(3, '</Environment>')
	end)
end

--
-- VS Linux implementation
--

if (_ACTION_VS and _LINUX_REMOTE) then
	require "vstudio"

	local vs = p.vstudio
	local vc = p.vstudio.vc2010
	local m = {}

	-- Register root dir

	p.api.register {
		name = "remoteprojectrootdir",
		scope = "project",
		kind = "string",
	}

	-- Register absolute library directories

	p.api.register {
		name = "absolutelinks",
		scope = "project",
		kind = "table",
	}

	-- Architecture from configuration

	p.override(vs, "archFromConfig", function(base, cfg, force)
		return base(cfg, false)
	end)

	-- Globals

	p.override(vc.elements, "globals", function(base, prj)
		local elements = base(prj)
		return table.join(elements, {
			m.rootNamespace,
			m.minimumVisualStudioVersion,
			m.applicationType,
			m.applicationTypeRevision,
			m.targetLinuxPlatform,
		})
	end)

	-- Keyword

	p.override(vc, "keyword", function(base, prj)
		vc.element("Keyword", nil, "Linux")
	end)

	-- Platform toolset

	p.override(vc, "platformToolset", function(base, cfg)
		vc.element("PlatformToolset", nil, "Remote_GCC_1_0")
	end)

	-- Configuration properties

	p.override(vc.elements, "configurationProperties", function(base, cfg)
		local elements = base(cfg)
		return table.join(elements, {
			m.remoteProjectDir,
		})
	end)

	-- Windows SDK desktop ARM support

	p.override(vc, "windowsSDKDesktopARMSupport", function(base, cfg)
	end)

	-- Property sheet group

	p.override(vc, "propertySheetGroup", function(base, prj)
		p.w('<ImportGroup Label="PropertySheets" />')
	end)

	-- Target extension

	p.override(vc, "targetExt", function(base, cfg)
		vc.element("TargetExt", nil, cfg.buildtarget.extension)
	end)

	-- Output properties

	p.override(vc.elements, "outputProperties", function(base, cfg)
		local elements = base(cfg)
		return table.join(elements, {
			m.customBuildBeforeTargets,
		})
	end)

	-- Warning level

	p.override(vc, "warningLevel", function(base, cfg)
		local map = {
			Off = "TurnOffAllWarnings",
			Extra = "EnableAllWarnings",
		}
		vc.element("WarningLevel", nil, map[cfg.warnings])
	end)

	-- Additional compile options

	p.override(vc, "additionalCompileOptions", function(base, cfg, condition)
		local opts = cfg.buildoptions
		if (cfg.cppdialect == "C++11") then
			table.insert(opts, "-std=c++11")
		elseif (cfg.cppdialect == "C++14") then
			table.insert(opts, "-std=c++14")
		elseif (cfg.cppdialect == "C++17") then	
			table.insert(opts, "-std=c++17")
		end

		if (#opts > 0) then
			opts = table.concat(opts, " ")
			vc.element("AdditionalOptions", condition, "%s %%(AdditionalOptions)", opts)
		end
	end)

	-- Additional dependencies

	p.override(vc, "additionalDependencies", function(base, cfg, explicit)
		local links
		local toolset = p.config.toolset(cfg)

		if (toolset) then
			links = toolset.getlinks(cfg, not explicit)
		else
			links = toolset.getlinks(cfg, explicit)
		end

		if (#links > 0) then
			links = table.concat(table.join(links, cfg.project.absolutelinks), ";")
			vc.element("AdditionalDependencies", nil, "%s;%%(AdditionalDependencies)", links)
		end
	end)

	-- Debug settings

	p.override(vc.elements, "debugSettings", function(base, cfg)
		local elements = base(cfg)
		return table.join(elements, {
			m.remoteDebuggingMode,
			m.preLaunchCommand,
		})
	end)

	-- Module functions

	function m.rootNamespace(prj)
		vc.element("RootNamespace", nil, prj.name)
	end

	function m.applicationType(prj)
		vc.element("ApplicationType", nil, "Linux")
	end

	function m.applicationTypeRevision(prj)
		vc.element("ApplicationTypeRevision", nil, "1.0")
	end

	function m.targetLinuxPlatform(prj)
		vc.element("TargetLinuxPlatform", nil, "Generic")
	end

	function m.minimumVisualStudioVersion(prj)
		vc.element("MinimumVisualStudioVersion", nil, "15.0")
	end

	function m.remoteProjectDir(cfg)
		vc.element("RemoteProjectDir", nil, cfg.project.remoteprojectrootdir)
	end

	function m.remoteDebuggingMode(cfg)
		vc.element("RemoteDebuggingMode", nil, "gdb")
	end

	function m.preLaunchCommand(cfg)
		vc.element("PreLaunchCommand", nil, "export DISPLAY=:0.0")
	end

end
