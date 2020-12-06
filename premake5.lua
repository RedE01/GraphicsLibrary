workspace "GraphicsLibrary"
    configurations { "Debug", "Release" }

project "GraphicsLibrary"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files {
        "src/*.h",
        "src/*.cpp",

        "src/Etc/**.h",
        "src/Etc/**.cpp",

        "src/Input/**.cpp"
    }

    filter "system:linux"
        defines "RGL_LINUX"
        links { "X11"}
        files {
            "src/Platform/Linux/**.h",
            "src/Platform/Linux/**.cpp"
        }

    filter "system:windows"
        defines "RGL_WINDOWS"
    
    filter "configurations:Debug"
		defines "RGL_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "RGL_RELEASE"
		optimize "On"
		runtime "Release"