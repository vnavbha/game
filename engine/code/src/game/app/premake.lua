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
postbuildcommands { "copy /y \"engine.ini\" \""..TARGET_DIR .. "\"" }
--vpaths { ["Headers/*"] = "**.h" } - works


