#include "Macro.h"
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <optional>

namespace Engine {

    #ifdef _WIN32
        class DLLEXP Window;
    #endif

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
}