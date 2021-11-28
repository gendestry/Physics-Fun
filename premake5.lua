workspace "Physics Fun"
	configurations { "Release" }
	
project "Physics Fun"
	kind "ConsoleApp"
	language "C++"
	location "Physics Fun"
	architecture "x64"
	
	targetdir 	"%{prj.location}/build/%{cfg.buildcfg}/bin"
	objdir 		"%{prj.location}/build/%{cfg.buildcfg}/obj"

	files { "**.h", "**.cpp" }

	filter "configurations:*"
		systemversion "latest"
		
		defines { "GLEW_STATIC" }
		
		includedirs { 
			"dependencies/glfw-3.3.5/include",
			"dependencies/glew-2.1.0/include",
			"dependencies/glm",
		}
		
		libdirs { 
			"dependencies/glfw-3.3.5/lib-vc2019",
			"dependencies/glew-2.1.0/lib/Release/x64"
		}
		
		links
		{
			"gdi32.lib",
			"opengl32",
			"glfw3.lib",
			"glew32s.lib"
		}

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"