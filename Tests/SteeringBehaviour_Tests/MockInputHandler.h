#pragma once
#include <unordered_map>
#include "Systems/InputHandler.h"

class MockInputHandler : public InputHandler {
public:
    bool isKeyPressed(sf::Keyboard::Key key) const override {
        auto it = keyState.find(key);
        if (it != keyState.end()) {
            return it->second;
        }
        return false;
    }

    sf::Vector2i getMousePosition(const sf::RenderWindow& window) const override {
        return mousePosition;
    }

    // Для симуляции нажатий клавиш
    void setKeyPressed(sf::Keyboard::Key key, bool pressed) {
        keyState[key] = pressed;
    }

    // Для симуляции движения мыши
    void setMousePosition(const sf::Vector2i& position) {
        mousePosition = position;
    }

private:
    std::unordered_map<sf::Keyboard::Key, bool> keyState;
    sf::Vector2i mousePosition{ 0, 0 };
};
