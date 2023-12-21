/*
    Application class is a class that will handle initialization
    of all resources needed by the client.

    It needs to be overwritten in the actual client project
*/

#pragma once
#include "Macro.h"
#include "Window.h"

#ifdef _WIN32
    #include "GfxDX/GfxBase.h"
#endif

namespace Engine {
    #ifdef _WIN32
        class DLLEXP Application;
    #endif
    
    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual int Run() = 0;

    protected:
        Window* pWindow = nullptr;
        GfxBase* pGfxBase = nullptr;
    };

    //Needs to be defined in client
    Application* CreateNewApp();
}