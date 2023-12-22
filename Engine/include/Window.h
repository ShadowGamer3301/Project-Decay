#pragma once
#include "Macro.h"
#ifdef __linux
    #include <SFML/Window.hpp>
    #include <SFML/Window/Window.hpp>
#endif
#ifdef _WIN32
    #include <Windows.h>
#endif
#include <optional>

namespace Engine {

    #ifdef _WIN32
    class DLLEXP Window
    {
    private:
        class WindowClass
        {
        public:
            static constexpr const wchar_t* GetName() noexcept { return L"Engine"; }
            static HINSTANCE GetInstance() noexcept { return wndClass.hInst; }
        private:
            WindowClass() noexcept;
            ~WindowClass();
            WindowClass(const WindowClass&) = delete;
            WindowClass operator=(const WindowClass&) = delete;

            static WindowClass wndClass;
            HINSTANCE hInst;
        };
    public:
        Window(LPCWSTR title);
        ~Window();

        std::optional<int> ProcessMessage();

        inline HWND GetWindowHandle() const noexcept { return hWnd; }
        void ChangeTitle(LPCWSTR title);

    private:
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

    private:
        HWND hWnd;
    };
    #endif
#ifdef __linux
    class Window
    {
    public:
        Window(std::string title);
        ~Window();

        Window(const Window&) = delete;
        Window operator=(const Window&) = delete;

        inline sf::Window* GetWindowPointer() const noexcept { return pWnd; }

        std::optional<int> ProcessMessage();

    private:
        sf::Window* pWnd;
    };

#endif
}