cpp_lib("system", "base")
links{
	"system.eastl"
}
cpp_create_unittest("system", "base")
links{
	"system.eastl",
	"system.base"
}
--vpaths { ["Headers/*"] = "**.h" } - works


