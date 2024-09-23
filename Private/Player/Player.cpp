#include "Player/Player.h"

Player::Player()
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(375.0f, 275.0f);
    speed = 200.0f;
}

void Player::update(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        shape.move(-speed * deltaTime, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        shape.move(speed * deltaTime, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        shape.move(0.0f, -speed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        shape.move(0.0f, speed * deltaTime);
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(shape);
}
