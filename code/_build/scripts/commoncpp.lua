dofile "common.lua"
dofile "libdeps.lua"

-- cpp

-- //--------------------------------------------------------------------------

function cpp_common_includes()
    includedirs(
    { 
        SRC_DIR,
        SRC_DIR .. "/system/eastl/include"
    })
end

function cpp_common()
    cpp_common_includes()
        disablewarnings({
        "4251"
    })
end

-- //--------------------------------------------------------------------------

function cpp_create_unittest(moduleName, projectName)
    unittestgeneratorcommand = BUILD_DIR .. "/_out/_bin/release/x64/tools.unittestgenerator.exe %s"
    print_info(unittestgeneratorcommand)
    os.executef(unittestgeneratorcommand, get_project_path(moduleName, projectName))

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

    cpp_common()
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
  local geneeratepath = SLN_DIR
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
        "WINDOWS",
        "WIN32_LEAN_AND_MEAN"
    }

  configuration("release")
    flags {"Optimize"}
    defines
    {
        "NDEBUG", 
        "WINDOWS",
        "WIN32_LEAN_AND_MEAN"
    }
  
end

-- //--------------------------------------------------------------------------

function cpp_lib(moduleName, projectName)
    project_common(moduleName, projectName)
    objdir(BUILD_DIR .. "/_obj")
    files({
        "**.cpp",
        "**.hpp",
        "**.h",
        "**.ini"
    })

    cpp_common_includes()
    kind("StaticLib")
end

function cpp_dyn_lib(moduleName, projectName)
    project_common(moduleName, projectName)
    objdir(BUILD_DIR .. "/_obj")
    files({
        "**.cpp",
        "**.hpp",
        "**.h",
        "**.ini"
    })
    disablewarnings({
        "4251"
    })
    cpp_common()
    kind("SharedLib")

    defines { "BUILD_" .. string.upper(moduleName) .. "_" .. string.upper(projectName)}
end

-- //--------------------------------------------------------------------------

function cpp_app(moduleName, projectName)
    project_common(moduleName, projectName)
    objdir(BUILD_DIR .. "/_obj")
    files({
        "**.cpp",
        "**.hpp",
        "**.h",
        "**.ini"
    })
    cpp_common()
    kind("ConsoleApp")
end

-- //--------------------------------------------------------------------------