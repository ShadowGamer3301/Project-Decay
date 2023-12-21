#include "Window.h"
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