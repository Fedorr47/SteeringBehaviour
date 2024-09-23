#include "Window/Window.h"

Window::Window(const std::string& title, const sf::Vector2u& size)
{
    setup(title, size);
}

Window::~Window()
{
    window.close();
}

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
    windowTitle = title;
    windowSize = size;
    isWindowOpen = true;
    window.create({ windowSize.x, windowSize.y }, windowTitle);
}

void Window::beginDraw()
{
    window.clear(sf::Color::Black);
}

void Window::endDraw()
{
    window.display();
}

void Window::update()
{
    handleEvents();
}

void Window::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            close();
    }
}

bool Window::isOpen() const
{
    return isWindowOpen;
}

void Window::close()
{
    isWindowOpen = false;
    window.close();
}

sf::RenderWindow* Window::getRenderWindow()
{
    return &window;
}

sf::Vector2u Window::getWindowSize() const
{
    return windowSize;
}
