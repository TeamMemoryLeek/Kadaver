-- CodeLite customizations

if (_ACTION == 'codelite') then
	require 'codelite'

	-- Modify linker library path

	premake.override(premake.modules.codelite.project, 'environment', function(base, prj)
		_p(3, '<Environment EnvVarSetName="&lt;Use Defaults&gt;" DbgSetName="&lt;Use Defaults&gt;">')
		_x(4, '<![CDATA[%s]]>', 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH;'.._MAIN_SCRIPT_DIR..'/../../bin')
		_p(3, '</Environment>')
	end)
end
