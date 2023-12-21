if(WIN32)
    file(GLOB EngineSRC "source/*.cxx" "source/GfxDX/*.cxx") #Look for all C++ source files (Windows version uses DirectX 11 renderer)
elseif(UNIX)
    file(GLOB EngineSRC "*/*.cxx" "*/GfxVK/*.cxx") #Look for all C++ source files (Linux version uses Vulkan 1.3 renderer)
endif()

add_library(Engine SHARED ${EngineSRC})

if(WIN32)
    target_compile_definitions(Engine PRIVATE UNICODE _WINDLL) #Mark project as DLL on Windows
    target_link_directories(Engine PUBLIC "../3rdParty/lib")
    target_link_libraries(Engine PUBLIC "DirectXTK.lib" "dxgi.lib") #Make sure we are linking SFMLs static libraries
endif()

target_include_directories(Engine PUBLIC "include" "../3rdParty/include")