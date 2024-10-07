add_languages("c++17")

add_rules("mode.release")
local depends = {
    "eigen"
}
add_requires(depends)

target("Utils")
    set_kind("static")
    add_packages(depends, {public = true})
    add_includedirs("Utils", {public = true})

target("Type-Test")
    set_kind("binary")
    set_targetdir(".")
    add_deps("Utils")
    add_files("UnitTests/00_TypeTest.cpp")

target("Util-Test")
    set_kind("binary")
    set_targetdir(".")
    add_deps("Utils")
    add_files("UnitTests/01_UtilTest.cpp")


target("Memory-Test")
    set_kind("binary")
    set_targetdir(".")
    add_deps("Utils")
    add_includedirs("MemorySystem", {public = true})
    add_files("UnitTests/03_MemoryTest.cpp")