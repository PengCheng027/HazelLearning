workspace "Hazel"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["GLAD"] = "Hazel/vendor/GLAD/include"
IncludeDir["ImGui"] = "Hazel/vendor/imgui"
-- Include a premake5.lua file form this path
include "Hazel/vendor/GLFW"
include "Hazel/vendor/GLAD"
include "Hazel/vendor/imgui"

project "Hazel"
    location "Hazel"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "hzpch.h"
    pchsource "%{prj.name}/src/hzpch.cpp"

    files
    {
        "%{prj.name}/src/HAZEL/Events/*.h",
        "%{prj.name}/src/HAZEL/Events/*.cpp",
        "%{prj.name}/src/HAZEL/Core/*.h",
        "%{prj.name}/src/HAZEL/Core/*.cpp",
        "%{prj.name}/src/HAZEL/*.h",
        "%{prj.name}/src/HAZEL/*.cpp",
        "%{prj.name}/src/*.h",
        "%{prj.name}/src/*.cpp",
        "%{prj.name}/src/Platform/Windows/*.h",
        "%{prj.name}/src/Platform/Windows/*.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HZ_PLATFORM_WINDOWS",
            "_MBCS",
            "HZ_BUILD_DLL",
            "HZ_DEBUG",
            "_CRT_SECURE_NO_WARNINGS",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{wks.location}bin\\Debug-windows-x86_64\\Hazel\\*.dll  %{wks.location}bin\\Debug-windows-x86_64\\Sandbox\\")
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"   
        defines "HZ_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "HZ_DIST"
        buildoptions "/MD"
        optimize "On"


project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        systemversion "latest"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "Hazel/vendor/spdlog/include",
            "Hazel/src"
        }

        links
        {
            "Hazel"
        }

        filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HZ_PLATFORM_WINDOWS"
        }

        filter "configurations:Debug"
            defines "HZ_DEBUG"
            buildoptions "/MDd"
            symbols "On"

        filter "configurations:Release"   
            defines "HZ_RELEASE"
            buildoptions "/MD"
            optimize "On"

        filter "configurations:Dist"
            defines "HZ_DIST"
            buildoptions "/MD"
            optimize "On"
