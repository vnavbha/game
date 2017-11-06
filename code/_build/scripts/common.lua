-- common
-- //-----------------------------------------------------------------------

function print_separator()
    print("--------------------------------------------------------------")
end

function print_info(info)
    print("[info] " .. info)
end
function print_warning(warning)
    print("[warn] " .. warning)
end
function print_err(error)
    print("[error!] " .. error)
end

function os.capture(cmd, raw)
    print_separator()
    print_info(cmd)
    local f = assert(io.popen(cmd, 'r'))
    local s = assert(f:read('*all'))
    print_info(s)
    print_separator()
    f:close()  
end

-- utils
function get_project_path(moduleName, projectName)
    return SRC_DIR .. "/" .. moduleName .. "/" .. projectName
end

function solution_compile(slnPath, slnConfig, platform, additionalArgs)
    command = '"' .. os.getenv("VSINSTALLDIR") .. "devenv.exe" .. '"'
    args =  "devenv.com " .. slnPath .. " /build " .. '"' .. slnConfig .. "|" .. platform .. '" ' .. additionalArgs
    print_info(args)
    os.capture(args, false)    
end

function project_include(moduleName, projectName)
    print_info(moduleName .. "." .. projectName)
    dofile(get_project_path(moduleName, projectName) .. "/premake.lua")
end

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