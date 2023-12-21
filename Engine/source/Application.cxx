#include "Application.h"

Engine::Application::Application()
{
#ifdef _WIN32
    pWindow = new Window(L"Test"); 
    pGfxBase = new GfxBase(pWindow);
#endif
}

Engine::Application::~Application()
{
    DELETE_ON_VAL(pGfxBase);
    DELETE_ON_VAL(pWindow);
}