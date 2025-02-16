add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate")
set_defaultmode("debug")
set_optimize("faster")
set_toolchains("gcc")
set_languages("c++23")
add_requires("glfw","spdlog","glm")

target("glad")
    set_kind("static")
    add_includedirs("modules/glad/include")
    add_files("modules/glad/src/**.c")

target("blocky-game")
    set_kind("binary")
    add_files("src/**.cpp")
    add_packages("glfw","spdlog","glm")
    add_deps("glad")
    add_includedirs("modules/glad/include","modules/stb/include", "include")
    after_build(function ()
        os.run("ln -sf $(projectdir)/res $(buildir)/$(plat)/$(arch)/$(mode)/")
    end)
