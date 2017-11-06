cpp_dyn_lib("system", "base")
links{
	"system.eastl"
}
system_eastl_configure()
postbuildcommands { "copy /y \"engine.ini\" \""..TARGET_DIR .. "\"" }

cpp_create_unittest("system", "base")
links{
	"system.eastl",
	"system.base"
}
system_eastl_configure()