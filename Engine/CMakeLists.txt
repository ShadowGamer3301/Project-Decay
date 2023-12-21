if(WIN32)
    file(GLOB EngineSRC "*/*.cxx" "*/GfxVK/*.cxx") #Look for all C++ source files (Windows version uses DirectX 11 renderer)
elseif(UNIX)
    file(GLOB EngineSRC "*/*.cxx" "*/GfxDX/*.cxx") #Look for all C++ source files (Linux version uses Vulkan 1.3 renderer)
endif()

add_library(Engine SHARED ${EngineSRC})

if(WIN32)
    target_compile_definitions(Engine PRIVATE UNICODE _WINDLL) #Mark project as DLL on Windows
endif()

target_include_directories(Engine PUBLIC "include")