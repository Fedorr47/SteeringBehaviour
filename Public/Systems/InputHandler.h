#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class InputHandler {
public:
    virtual ~InputHandler() = default;

    virtual bool isKeyPressed(sf::Keyboard::Key key) const = 0;
    virtual sf::Vector2i getMousePosition(const sf::RenderWindow& window) const = 0;
};