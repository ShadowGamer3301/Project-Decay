#include "Application.h"
#include "GfxVK/GfxBase.h"

Engine::Application::Application()
{
#ifdef _WIN32
    pWindow = new Window(L"Test"); 
    pGfxBase = new GfxBase(pWindow);
#else
    pWindow = new Window("Test");
    pGfxBase = new GfxBase(pWindow);
#endif
}

Engine::Application::~Application()
{
    DELETE_ON_VAL(pGfxBase);
    DELETE_ON_VAL(pWindow);
}