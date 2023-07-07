project "GLAD"
    kind "StaticLib"
    language "C"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:linux"
            pic "On"
            systemversion "latest"
            staticruntime "On"

    filter "system:windows"
            systemversion "latest"
            staticruntime "On"

    filter "configurations:Debug"
            runtime "Debug"
            buildoptions "/MT"
            symbols "On"

    filter "configurations:Release"
            runtime "Release"
            buildoptions "/MT"
            symbols "On"