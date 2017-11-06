--Builds vs2015
BUILD_DIR = path.getabsolute(os.getcwd())
PROJECT_ROOT_DIR = path.getabsolute(BUILD_DIR .. "/../..")
SLN_DIR = BUILD_DIR .. "/_solutions"
EXTERNAL_DIR = path.getabsolute(PROJECT_ROOT_DIR .. "/external")
SRC_DIR = path.getabsolute(PROJECT_ROOT_DIR .. "/code/src")
TARGET_DIR = BUILD_DIR .. "/_out/_bin/$(Configuration)/$(Platform)"
TOOLS_DIR = SRC_DIR .. "/tools"
UNITTESTGENERATOR_PATH = ""

debugdir=TARGET_DIR
dofile "./scripts/common.lua"
print("--------------------------------------------------------------")

print_info("builddir: " ..  BUILD_DIR)
print_info("externaldir: " ..  EXTERNAL_DIR)
print_info("srcdir: " ..  SRC_DIR)
print_info("targetdir: " ..  TARGET_DIR)

print("--------------------------------------------------------------")

dofile "./scripts/commoncs.lua"
dofile "./scripts/commoncpp.lua"
dofile "./scripts/configure.lua"
dofile "./scripts/configs/assimp.lua"

print("--------------------------------------------------------------")

cs_solution("tools")
	project_include("tools", "unittestgenerator")
	solution_compile(SLN_DIR .. "/tools.sln","release","x64","")
	
print("--------------------------------------------------------------")

cpp_solution("engine")
	group("system")
		project_include("system", "eastl")
		project_include("system", "base")
		project_include("system", "resource")
		project_include("system", "render")

	group("runtime")
		project_include("runtime", "render")

	group("packer")
		project_include("packer", "render")

	group("game")
		project_include("game", "app")