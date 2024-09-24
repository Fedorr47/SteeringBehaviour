#pragma once
#include "InputHandler.h"

class RealInputHandler : public InputHandler {
public:
    bool isKeyPressed(sf::Keyboard::Key key) const override {
        return sf::Keyboard::isKeyPressed(key);
    }

    sf::Vector2i getMousePosition(const sf::RenderWindow& window) const override {
        return sf::Mouse::getPosition(window);
    }
};