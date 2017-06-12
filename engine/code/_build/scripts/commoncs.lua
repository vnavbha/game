
dofile "common.lua"

-- cs

-- //--------------------------------------------------------------------------

function cs_solution(solutionName)
  local generatepath = BUILD_DIR .. "/_solutions"
  print_info("processing solution " .. solutionName .. " at " .. generatepath)
  solution(solutionName)
    configurations { "debug", "release" }
    location(generatepath)
    language("c#")
    
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

    if(_ACTION == "build") then
        util_compile(generatepath.. "/solutionName" .. ".sln", "debug", "x64", "")
    end
end

-- //--------------------------------------------------------------------------

function cs_lib(moduleName, projectName)
    project_common(moduleName, projectName)
    files("**.cs")
    excludes { "obj/**" }
    kind("StaticLib")    

    if(_ACTION == "clean") then
        os.rmdir(path.getabsolute(os.getcwd()) .. "/obj")
    end
end

-- //--------------------------------------------------------------------------

function cs_app(moduleName, projectName)
    project_common(moduleName, projectName)    
    files("**.cs")
    excludes { "obj/**" }
    kind("ConsoleApp")

    if(_ACTION == "clean") then
        os.rmdir(path.getabsolute(os.getcwd()) .. "/obj")    
    end
end

-- //--------------------------------------------------------------------------