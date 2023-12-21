#include "Window.h"
#include "Exception.h"

#ifdef __linux

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

Engine::Window::Window(std::string title)
{
    pWnd = new sf::Window(sf::VideoMode(800, 600), title, sf::Style::Titlebar | sf::Style::Close);
}

Engine::Window::~Window()
{
    DELETE_ON_VAL(pWnd);
}

std::optional<int> Engine::Window::ProcessMessage()
{
    sf::Event ev;
    while(pWnd->pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
            return 0;
    }

    return {};
}

#endif

#ifdef _WIN32

Engine::Window::WindowClass Engine::Window::WindowClass::wndClass;

Engine::Window::WindowClass::WindowClass() noexcept
    : hInst(GetModuleHandle(nullptr))
{
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetInstance();
    wcex.hCursor = nullptr;
    wcex.lpszClassName = GetName();
    wcex.lpfnWndProc = WndProc;
    
    RegisterClassEx(&wcex);
}

Engine::Window::WindowClass::~WindowClass()
{
    UnregisterClass(GetName(), GetInstance());
}

LRESULT Engine::Window::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hWnd, msg, wp, lp);
}

std::optional<int> Engine::Window::ProcessMessage()
{
    MSG msg = { 0 };

    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return msg.wParam; //This is where exit code is stored

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return {};
}

Engine::Window::Window(LPCWSTR title)
{
    hWnd = CreateWindowExW(0, WindowClass::GetName(), title, WS_OVERLAPPED | WS_SYSMENU, 0, 0,
        800, 600, nullptr, nullptr, WindowClass::GetInstance(), nullptr);

    if (!hWnd) throw Exception();

    ShowWindow(hWnd, SW_SHOW);
}

Engine::Window::~Window()
{
    DestroyWindow(hWnd);
}

#endif