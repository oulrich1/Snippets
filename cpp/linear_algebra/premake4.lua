-- First, write the library..
-- Then compile the lib into static library..
--      and then test with a different configuration 
--      that tests the static lib

solution "Linear Algebra Solution"

    root = "."

    configurations {"Release", "Debug"}

    -- project "Lib"
    --         kind "StaticLib"
    --         language "C"
    --         files {"./lib/**.c"}
    --         includedirs {"./include"}
    --         location "./build/lib"
    --         targetdir "build/lib"
    --         targetname "target-lib"
    
    project "linear_algebra"
        kind "ConsoleApp"
        language "C++"
        -- files {"main.c", doesim_root.."/lib/string.c", doesim_root.."/bdl/lexer.c", doesim_root.."/bdl/lexer/attr.c"}
        files {"*.cpp"}
            -- , lib_root.."/**.cpp", lib_root.."/ashrae/**.cpp", 
            --           lib_root.."/building/**.cpp", lib_root.."/equipment/**.cpp",
            --           lib_root.."/phys/**.cpp", lib_root.."/schedule/**.cpp" }
        buildoptions {"-std=c++11", "-g"} --, "-Werror"}
        includedirs {   
                        -- doesim_root.."/include/**", 
                        -- doesim_root.."/include/",
                        "$HOME/opt/openmpi/include" }
        libdirs {"/usr/local/lib", "$HOME/opt/openmpi/lib"}
        location "build"
        -- targetdir "bin"
        targetname "test_matricies"
        
        configuration "Release"
            links {"pthread", "gsl", "gslcblas", "m"}

