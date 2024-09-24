#pragma once
#include <SFML/Graphics.hpp>

struct GameSettings {
    float maxForce;
    float maxSpeed;
    sf::RenderWindow& window;
};