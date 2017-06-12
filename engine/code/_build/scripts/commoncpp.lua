dofile "common.lua"

-- cpp

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
    kind("StaticLib")    
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
    kind("ConsoleApp")
end

-- //--------------------------------------------------------------------------