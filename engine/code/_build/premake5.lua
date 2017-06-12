--Builds vs2013
BUILD_DIR = path.getabsolute(os.getcwd())
TARGET_DIR = BUILD_DIR .. "/_out/_bin/$(Configuration)/$(Platform)"

dofile "./scripts/commoncs.lua"
dofile "./scripts/commoncpp.lua"
dofile "./scripts/configure.lua"

print("--------------------------------------------------------------")
print_info("builddir: " ..  BUILD_DIR)
print("--------------------------------------------------------------")

-- compile tools

cpp_solution("platform")
	project_include("system", "eastl")
