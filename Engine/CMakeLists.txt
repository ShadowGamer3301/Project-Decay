file(GLOB EngineSRC "*/*.cpp" "*/*.cxx" "*/*.cc") #Look for all C++ source files


add_library(Engine SHARED ${EngineSRC})
target_compile_definitions(Engine PRIVATE UNICODE _WINDLL)
target_include_directories(Engine PUBLIC "include")