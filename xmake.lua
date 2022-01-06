add_rules("mode.debug", "mode.release")

target("cstlike")
    set_kind("static")
    set_languages("c17")
    add_includedirs("include")
    add_headerfiles("include/*.h")
    add_files("src/*.c")
