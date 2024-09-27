#pragma once
#include <SFML/Graphics.hpp>

struct GameSettings {
    GameSettings(
        float maxForce, 
        float maxSpeed, 
        sf::RenderWindow& window,
        bool IsLimitFPS, 
        unsigned int MaxFps
    ) :
        maxForce(maxForce),
        maxSpeed(maxSpeed),
        window(window),
        IsLimitFPS(IsLimitFPS),
        MaxFps(MaxFps)
    {}
    float maxForce;
    float maxSpeed;
    unsigned int MaxFps = 60;
    bool IsLimitFPS = false;
    sf::RenderWindow& window;
};