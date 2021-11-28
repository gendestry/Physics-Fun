workspace "Physics Fun"
	configurations { "Release" }
	startproject "Physics Fun"
	architecture "x86_64"

project "glfw"
	location ("dependencies/glfw")
	kind "StaticLib"
	targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
	objdir "bin-int/%{cfg.buildcfg}/%{prj.name}"

	files {
		-- all platforms
        "%{prj.location}/src/context.c",
        "%{prj.location}/src/egl_context.c",
        "%{prj.location}/src/egl_context.h",
        "%{prj.location}/src/init.c",
        "%{prj.location}/src/input.c",
        "%{prj.location}/src/internal.h",
        "%{prj.location}/src/monitor.c",
        "%{prj.location}/src/osmesa_context.c",
        "%{prj.location}/src/osmesa_context.h",
        "%{prj.location}/src/vulkan.c",
        "%{prj.location}/src/window.c",
		-- win only
        "%{prj.location}/src/wgl_context.c",
        "%{prj.location}/src/wgl_context.h",
        "%{prj.location}/src/win32_init.c",
        "%{prj.location}/src/win32_joystick.c",
        "%{prj.location}/src/win32_joystick.h",
        "%{prj.location}/src/win32_monitor.c",
        "%{prj.location}/src/win32_platform.h",
        "%{prj.location}/src/win32_thread.c",
        "%{prj.location}/src/win32_time.c",
        "%{prj.location}/src/win32_window.c"
    }

    defines { 
        "_GLFW_WIN32",
        "_CRT_SECURE_NO_WARNINGS"
    }

project "glad"
	location ("dependencies/glad")
	kind "StaticLib"
	targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
	objdir "bin-int/%{cfg.buildcfg}/%{prj.name}"

	files {
		"%{prj.location}/src/gl.c"
	}

	includedirs {
		"%{prj.location}/include/"
	}

project "imgui"
	location ("dependencies/imgui")
	kind "StaticLib"
	targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
	objdir "bin-int/%{cfg.buildcfg}/%{prj.name}"

	files {
		"%{prj.location}/*.cpp",
		"%{prj.location}/backends/imgui_impl_glfw.cpp",
		"%{prj.location}/backends/imgui_impl_opengl3.cpp",
		"%{prj.location}/misc/cpp/imgui_stdlib.cpp"
	}

	includedirs {
		"%{prj.location}",
		"%{wks.location}/dependencies/glfw/include"
	}


project "Physics Fun"
	kind "ConsoleApp"
	language "C++"
	location "Physics Fun"
	
	targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
	objdir	  "bin-int/%{cfg.buildcfg}/%{prj.name}"

	files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }

	defines {
		"GLFW_INCLUDE_NONE"
	}

	filter "configurations:*"
		systemversion "latest"
		
		includedirs { 
			"dependencies/glfw/include",
			"dependencies/glad/include",
			"dependencies/glm",
			"dependencies/imgui"
		}
		
		links {
			"glfw",
			"glad",
			"imgui"
		}

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"