workspace "DynCall"
	location "Build"
	configurations { "Debug", "Release" }
	platforms { "X64" }
	startproject "DynCall"
	pic "On"
	systemversion "10.0.15063.0"
	characterset "ASCII"

project "DynCall"
	kind "ConsoleApp"
	targetname "DynCall"
	language "C++"
	targetdir "Binary"
	includedirs { }

	files { "**.hpp", "**.h", "**.cpp", "**.c", "**.asm", "**.inc", "**.def"}
	removefiles { }
 
	vpaths {
		["Headers/*"] = { "**.hpp", "**.h" }
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
	os.mkdir("Binary")

-- Cleanup
if _ACTION == "clean" then
	os.rmdir("Binary");
	os.rmdir("Build");
end
