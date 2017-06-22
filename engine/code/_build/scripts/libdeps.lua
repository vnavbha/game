---
-- Allow static library projects to link in their dependencies. Visual Studio
-- doesn't support this out of the box, so I need to manually add items to
-- the list of additional dependencies.
---

local p = premake

function additionalDeps(cfg)
    local links = p.config.getlinks(cfg, "siblings", "fullpath")
    print("links " .. table.concat(links, ";"))
    if #links > 0 then
        links = path.translate(table.concat(links, ";"))
        p.x('<AdditionalDependencies>%s;%%(AdditionalDependencies)</AdditionalDependencies>', links)
    end
end

p.override(p.vstudio.vc2010.elements, "link", function(base, cfg, explicit)
    local calls = base(cfg, explicit)
    print("project: " .. cfg.objdir .. " kind " .. cfg.kind)
    if cfg.kind == p.SHAREDLIB then
        table.insert(calls, additionalDeps)
    end
    return calls
end)