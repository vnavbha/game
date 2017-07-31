cpp_app("game", "app")
links{
	"system.eastl",
	"system.base",
	"system.resource",
	"runtime.render",
	"runtime.app",
	
	"dxgi.lib",
	"d3d11.lib"
}
--vpaths { ["Headers/*"] = "**.h" } - works


