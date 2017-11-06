cpp_dyn_lib("system", "eastl")
defines(
{
		"EA_DLL",
		"BUILD_EASTL"
})
includedirs(
{ 
	"include"
})
removefiles {"test/**"}
removefiles {"benchmark/**"}
removefiles {"doc/**"}

function system_eastl_configure()
	defines(
	{
			"EA_DLL"
	})  
end