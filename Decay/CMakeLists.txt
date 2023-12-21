file(GLOB DecaySRC "*/*.cpp" "*/*.cxx" "*/*.cc") #Look for all C++ source files

add_executable(Decay ${DecaySRC})
target_compile_definitions(Decay PRIVATE UNICODE)
target_include_directories(Decay PUBLIC "../Engine/include" "../3rdParty/include")

if(WIN32)
	target_link_libraries(Decay PRIVATE Engine)
elseif(UNIX)
	target_link_libraries(Decay PRIVATE Engine "libsfml-window.so")
endif()