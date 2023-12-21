# Project-Decay
FOSS remake of Half-Life Decay

# 3rd Party software
WARNING! This project includes prebuilt binaries for: DirectXTK (windows x64) by Microsoft.
All of them can be found in 3rdParty directory.

# Linux build support
Since it's my first big project with Vulkan, I might struggle with implementing features into Linux build,
which means that this build might be a little bit less stable or lacking some features present in the 
windows version which uses DirectX 11 for rendering.

# Building
## Building on Windows (Visual Studio 22)
In order to build project on Windows you will need:
- Windows 10 SDK or Windows 11 SDK
- MSVC or any other compiler supporting C++20 standard
- CMake support for Visual Studio (can be enabled in Visual Studio Installer)

## Building on Linux
In order to build project on Linux you will need:
- Clang or any other compiler supporting C++20 standard
- Vulkan Devkit, SFML (they should be avaliable in yours distro package manager)
- CMake in Version 3.12 or newer