workspace "PhysicsFun"
	configurations { "Release" }
	startproject "PhysicsFun"
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
        -- "%{prj.location}/src/wgl_context.c",
        -- "%{prj.location}/src/wgl_context.h",
        -- "%{prj.location}/src/win32_init.c",
        -- "%{prj.location}/src/win32_joystick.c",
        -- "%{prj.location}/src/win32_joystick.h",
        -- "%{prj.location}/src/win32_monitor.c",
        -- "%{prj.location}/src/win32_platform.h",
        -- "%{prj.location}/src/win32_thread.c",
        -- "%{prj.location}/src/win32_time.c",
        -- "%{prj.location}/src/win32_window.c"
    }

	filter "system:windows"
        files
        {
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

        defines 
        { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "system:linux"
        files
        {
            "%{prj.location}/src/glx_context.c",
            "%{prj.location}/src/glx_context.h",
            "%{prj.location}/src/linux_joystick.c",
            "%{prj.location}/src/linux_joystick.h",
            "%{prj.location}/src/posix_time.c",
            "%{prj.location}/src/posix_time.h",
            "%{prj.location}/src/posix_thread.c",
            "%{prj.location}/src/posix_thread.h",
            "%{prj.location}/src/x11_init.c",
            "%{prj.location}/src/x11_monitor.c",
            "%{prj.location}/src/x11_platform.h",
            "%{prj.location}/src/x11_window.c",
            "%{prj.location}/src/xkb_unicode.c",
            "%{prj.location}/src/xkb_unicode.h"
        }

        defines 
        { 
            "_GLFW_X11"
        }

    -- defines { 
    --     "_GLFW_WIN32",
    --     "_CRT_SECURE_NO_WARNINGS"
    -- }

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


project "PhysicsFun"
	kind "ConsoleApp"
	language "C++"
	location "PhysicsFun"
	
	targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
	objdir	  "bin-int/%{cfg.buildcfg}/%{prj.name}"

	files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }

	defines {
		"GLFW_INCLUDE_NONE"
	}

	filter "system:linux"
        links   {
			"dl",
			"pthread",
			"X11"
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