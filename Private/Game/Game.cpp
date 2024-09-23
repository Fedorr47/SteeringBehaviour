#include "Game/Game.h"

Game::Game() : window("Simple SFML Game with EnTT", { 800, 600 })
{
    createPlayer(); 
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        sf::Time deltaTime = clock.restart();
        update(deltaTime.asSeconds());
        render();
    }
}

void Game::processEvents()
{
    window.update();
}

void Game::update(float deltaTime)
{
    inputSystem.update(registry, deltaTime);
    movementSystem.update(registry, deltaTime);
}

void Game::render()
{
    window.beginDraw();
    renderSystem.render(registry, *window.getRenderWindow());
    window.endDraw();
}

void Game::createPlayer()
{
    auto player = registry.create();

    registry.emplace<PositionComponent>(player, sf::Vector2f(375.0f, 275.0f));

    registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 200.0f);

    sf::RectangleShape shape(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Green);
    registry.emplace<ShapeComponent>(player, shape);
}
