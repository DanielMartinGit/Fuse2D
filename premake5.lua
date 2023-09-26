workspace("Fuse2D")
  architecture "x64"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

configurations
{
  "Debug",
  "Release"
}

-- Fuse2D API Module
project "Fuse2D"
	location "Fuse2D"
	kind "StaticLib"
	language "C++"

	targetdir ("Build/Executable/" .. outputDir .. "/%{prj.name}")
	objdir ("Build/Objects/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.hpp",
		"%{prj.name}/**.inl",
		"%{prj.name}/**.dll",
		"%{prj.name}/**.lib",
	}

	includedirs
	{
		"%prj.name/Vendor/Entt/",
		"%prj.name/Vendor/GLFW/",
		"%prj.name/Vendor/GLM/",
		"%prj.name/Vendor/GLAD/",
		"%prj.name/Vendor/STB/",
		"%prj.name/Vendor/Box2D/include",
		"$(SolutionDir)"
	}

	links
	{
		"glfw3",
	}

	libdirs
	{
		"Fuse2D/Vendor/Libraries/GLFW/",
		"Fuse2D/Vendor/Libraries/Fuse2D/",
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "10.0.22000.0"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} ../Fuse2D/Vendor/Libraries/Fuse2D")
		}

	filter "configurations.Debug"
		symbols "On"

	filter "configurations.Release"
		optimize "On"
	
	filter { "system:windows", "configurations:Debug"}
		buildoptions "/MDd"
	filter { "system:windows", "configurations:Release"}
		buildoptions "/MD"

-- Renderer Module
project "Fuse2D-Renderer"
	location "Fuse2D-Renderer"
	kind "StaticLib"
	language "C++"

	targetdir ("Build/Executable/" .. outputDir .. "/%{prj.name}")
	objdir ("Build/Objects/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"$(SolutionDir)",
	}

	links
	{ 
		"Fuse2D",
	}	

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "10.0.22000.0"

	filter "configurations.Debug"
		symbols "On"

	filter "configurations.Release"
		optimize "On"

	filter { "system:windows", "configurations:Debug"}
		buildoptions "/MDd"
	filter { "system:windows", "configurations:Release"}
		buildoptions "/MD"

project "Fuse2D-Scripting"
	location "Fuse2D-Scripting"
	kind "StaticLib"
	language "C++"

	targetdir ("Build/Executable/" .. outputDir .. "/%{prj.name}")
	objdir ("Build/Objects/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.hpp",
		"%{prj.name}/**.inl",
		"%{prj.name}/**.dll",
		"%{prj.name}/**.lib",
	}

	includedirs
	{
		"$(SolutionDir)"
	}

	links
	{
		"glfw3",
	}

	libdirs
	{
		"Fuse2D/Vendor/Libraries/Fuse2D/"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "10.0.22000.0"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} ../Fuse2D/Vendor/Libraries/Fuse2D")
		}

	filter "configurations.Debug"
		symbols "On"

	filter "configurations.Release"
		optimize "On"
	
	filter { "system:windows", "configurations:Debug"}
		buildoptions "/MDd"
	filter { "system:windows", "configurations:Release"}
		buildoptions "/MD"

-- Sandbox Module
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("Build/Executable/" .. outputDir .. "/%{prj.name}")
	objdir ("Build/Objects/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"$(SolutionDir)",
	}

	links
	{ 
		"Fuse2D",
	}	

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "10.0.22000.0"

	filter "configurations.Debug"
		symbols "On"

	filter "configurations.Release"
		optimize "On"

	filter { "system:windows", "configurations:Debug"}
		buildoptions "/MDd"
	filter { "system:windows", "configurations:Release"}
		buildoptions "/MD"