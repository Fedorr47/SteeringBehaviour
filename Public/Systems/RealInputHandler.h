#pragma once
#include "InputHandler.h"

class GameInputHandler : public InputHandler {
public:
    virtual bool isKeyPressed(sf::Keyboard::Key key) const override {
        return sf::Keyboard::isKeyPressed(key);
    }

    virtual sf::Vector2i getMousePosition(const sf::RenderWindow& window) const override {
        return sf::Mouse::getPosition(window);
    }
};