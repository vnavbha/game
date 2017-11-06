cpp_dyn_lib("system", "resource")
links{
	"system.eastl",
	"system.base"
}
system_eastl_configure();

cpp_create_unittest("system", "resource")
links{
	"system.eastl",
	"system.resource",
	"system.base"
}
system_eastl_configure();