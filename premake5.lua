workspace "OpenGLPractice"
    architecture "x64"
	language "C++"
    
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

	targetdir ("bin/" .. outputdir)
	objdir ("bin-obj/" .. outputdir)

	includedirs
	{
		"Dependencies/GLFW/include"
	}

	links
	{
		"GLFW"
	}
