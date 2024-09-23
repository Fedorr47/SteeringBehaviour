#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    float speed;
};
