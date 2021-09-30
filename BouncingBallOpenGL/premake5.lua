workspace "BouncingBallOpenGL"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GameEngine"
	location "GameEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	
	targetdir ("%{prj.name}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{prj.name}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.inl"
	}

	includedirs
	{
		"%{prj.name}/dependencies/GLEW/include",
		"%{prj.name}/dependencies/GLFW/include",
		"%{prj.name}/src/vendor"

	}

	libdirs
	{
		"%{prj.name}/dependencies/GLEW/lib/Release/Win32",
		"%{prj.name}/dependencies/GLFW/lib-vc2019"
	}

	links 
	{ 
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GLEW_STATIC",
			"EN_BUILD",
			"WIN32"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

		defines
		{
			"GLEW_STATIC",
			"WIN32",
			"EN_DEBUG"
		}
		links
		{
			"glfw3.lib",
			"glew32s.lib"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

		links
		{
			"glfw3.lib",
			"glew32s.lib"
		}
		

project "BouncingBall"
	location "BouncingBall"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	
	targetdir ("%{prj.name}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{prj.name}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.inl"
	}

	includedirs
	{
		"%{prj.name}/../GameEngine/src",
		"%{prj.name}/../GameEngine/src/vendor",
		"%{prj.name}/../GameEngine/dependencies/GLEW/include",
		"%{prj.name}/../GameEngine/dependencies/GLFW/include"
	}

	libdirs
	{
	}

	links 
	{ 
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

		links
		{
		}
		

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

		links
		{
		}