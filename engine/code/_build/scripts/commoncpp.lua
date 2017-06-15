dofile "common.lua"

-- cpp

-- //--------------------------------------------------------------------------

function cpp_common_includes()
    includedirs(
    { 
        SRC_DIR .. "/system/eastl/include"
    })
end

-- //--------------------------------------------------------------------------

function cpp_create_unittest(moduleName, projectName)
    if(os.isdir("_unittest") == false) then
        return
    else
        removefiles {"_unittest/**"}
    end

    local unittestName = projectName .. ".unittest"
    project_common(moduleName, unittestName)
    objdir(BUILD_DIR .. "/_obj")
    files({
        "_unittest/**.cpp",
        "_unittest/**.hpp",
        "_unittest/**.h"
    })

    cpp_common_includes()
    includedirs(
    { 
        "$(VCInstallDir)UnitTest/include"
    })
    libdirs(
    {
        "$(VCInstallDir)UnitTest/lib"
    })

    kind("SharedLib")
end

-- //--------------------------------------------------------------------------

function cpp_solution(solutionName)
  local geneeratepath = BUILD_DIR .. "/_solutions"
  print_info("processing solution " .. solutionName .. " at " .. geneeratepath)
  solution(solutionName)
    configurations { "debug", "release" }
    location(geneeratepath)
    language("c++")
    
    platforms({ "x64" })
  
  configuration("debug")
    flags {"Symbols"}
    defines 
    {
        "DEBUG", 
    }

  configuration("release")
    flags {"Optimize"}
    defines
    {
        "NDEBUG", 
    }
  
end

-- //--------------------------------------------------------------------------

function cpp_lib(moduleName, projectName)
    project_common(moduleName, projectName)
    objdir(BUILD_DIR .. "/_obj")
    files({
        "**.cpp",
        "**.hpp",
        "**.h"
    })
    cpp_common_includes()
    kind("StaticLib")

    cpp_create_unittest(moduleName, projectName)
end

-- //--------------------------------------------------------------------------

function cpp_app(moduleName, projectName)
    project_common(moduleName, projectName)
    objdir(BUILD_DIR .. "/_obj")
    files({
        "**.cpp",
        "**.hpp",
        "**.h"
    })
    cpp_common_includes()
    kind("ConsoleApp")
end

-- //--------------------------------------------------------------------------