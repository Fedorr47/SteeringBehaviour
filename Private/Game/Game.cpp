#include "Game/Game.h"

Game::Game() : window("Simple SFML Game", { 800, 600 })
{
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    window.update();
}

void Game::update()
{
    sf::Time deltaTime = clock.restart();
    float delta = deltaTime.asSeconds();

    player.update(delta);
}

void Game::render()
{
    window.beginDraw();

    player.render(*window.getRenderWindow()); 

    window.endDraw();
}
