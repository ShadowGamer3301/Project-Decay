#include "Application.h"

Engine::Application::Application()
{
    pWindow = new Window("Test");
}

Engine::Application::~Application()
{
    DELETE_ON_VAL(pWindow);
}