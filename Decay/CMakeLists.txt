file(GLOB DecaySRC "*/*.cpp" "*/*.cxx" "*/*.cc") #Look for all C++ source files

add_executable(Decay ${DecaySRC})
target_compile_definitions(Decay PRIVATE UNICODE)
target_include_directories(Decay PUBLIC "../Engine/include")
target_link_libraries(Decay PRIVATE Engine "libsfml-window.so")