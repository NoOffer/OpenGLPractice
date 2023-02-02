workspace "OpenGLPractice"
    architecture "x64"
    
	configurations
	{
		"Debug",
		"Release"
	}

	filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}"

project "OpenGLPractice"
	location "OpenGLPractice"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-obj/" .. outputdir)

	-- pchheader "pch.h"
	-- pchsource "%{prj.name}/src/pch.cpp"
	
	files
	{
		"%{prj.name}/glad.c",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/vendor"
	}
	
	removefiles
	{
		"%{prj.name}/src/vendor/imgui/main.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/vendor",
		"%{prj.name}/Dependencies/GLFW/include",
		"%{prj.name}/Dependencies/GLAD/include"
	}

	links
	{
		"%{prj.location}/Dependencies/GLFW/lib/glfw3.lib",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		staticruntime "off"

		defines
		{
			"PLATFORM_WINDOWS"
		}
