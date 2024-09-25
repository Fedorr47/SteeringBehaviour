#pragma once
#include <SFML/Graphics.hpp>

struct GameSettings {
    float maxForce;
    float maxSpeed;
    sf::RenderWindow& window;
    bool IsLimitFPS = false;
    unsigned int MaxFps = 60;
};