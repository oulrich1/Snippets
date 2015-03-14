solution "Solution"
    configurations {"Release", "Debug"}
        project "Polynomial"
                kind "ConsoleApp"
                language "C"
                files {"*.c"}
                buildoptions {"-std=c99", "-Werror"}
                -- includedirs {"include"}
                -- libdirs {"build/lib"}
                -- location "build/main"
                -- targetdir "bin"
                targetname "poly"
                configuration "Release"
                        links {"pthread", "m"}
