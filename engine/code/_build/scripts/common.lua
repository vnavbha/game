-- common
-- //-----------------------------------------------------------------------

function print_info(info)
    print("[info] " .. info)
end
function print_warning(warning)
    print("[warn] " .. warning)
end
function print_err(error)
    print("[warn] " .. error)
end

function setup_vs()
    command = os.getenv("VSINSTALLDIR") .. "devenv.exe"
    args = slnPath .. "/build " ..config .. "|" .. platform .. " " .. additionalArgs
    print_info(command " " .. args)
end

function solution_compile(slnPath, config, platform, additionalArgs)
    command = "devenv.exe"
    args = slnPath .. "/build " ..config .. "|" .. platform .. " " .. additionalArgs
    print_info(command " " .. args)
end

function project_include(moduleName, projectName)
    print_info(moduleName .. "." .. projectName)
    dofile("../src/" .. moduleName .. "/" .. projectName .. "/premake.lua")
end

-- utils

function get_project_pesudonym(moduleName, projectName)
    local projectPseudoNym = moduleName .. "." .. projectName
    return projectPseudoNym
end
-- //-----------------------------------------------------------------------

function project_common(moduleName, projectName)
    local projectPseudoNym = get_project_pesudonym(moduleName, projectName)

    project(projectPseudoNym)

    local generatedLocation = path.getabsolute(os.getcwd())
    --print_info("generating " .. generatedLocation)
    location(generatedLocation)

    local outDir = path.getabsolute(TARGET_DIR)
    targetdir (outDir)

    local vpathDir = "../src/" .. moduleName .. "/" .. projectName .. "/*"
    --print_info("vpaths " .. vpathDir)
    vpaths { ["*"] = vpathDir }

    libdirs {
        outDir
    }
        
end

-- //-----------------------------------------------------------------------