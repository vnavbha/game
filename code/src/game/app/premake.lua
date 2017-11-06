cpp_app("game", "app")
links{
	"system.eastl",
	"system.base",
	"system.resource",
	"system.render",
	"runtime.render",
}
system_eastl_configure();
--vpaths { ["Headers/*"] = "**.h" } - works
