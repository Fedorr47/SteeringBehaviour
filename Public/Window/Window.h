#pragma once
#include <SFML/Graphics.hpp>

class Window
{
public:
    Window(const std::string& title, const sf::Vector2u& size);
    ~Window();

    void beginDraw();
    void endDraw();

    void update();

    bool isOpen() const;
    void close();

    sf::RenderWindow* getRenderWindow();
    sf::Vector2u getWindowSize() const;

private:
    void setup(const std::string& title, const sf::Vector2u& size);
    void handleEvents();

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    std::string windowTitle;
    bool isWindowOpen;
};
