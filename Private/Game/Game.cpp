#include "Game/Game.h"
#include "entt/entt.hpp"
#include "Player/Player.h"
#include "Components/Components.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"

Game::Game() : 
    window("Steering Behaviour with EntityManager", { 800, 600 }),
    settings{ 500.0f, 200.0f, *window.getRenderWindow() },
    entityManager(settings, inputHandler)
{
    active_entity.push_back(entityManager.createPlayer(false));
    active_entity.push_back(entityManager.createNonPlayer());
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        sf::Time deltaTime = clock.restart();
        update(deltaTime.asSeconds());
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.getRenderWindow()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::LostFocus) {
            entityManager.SetFocusState(false);
        }
        else if (event.type == sf::Event::GainedFocus) {
            entityManager.SetFocusState(true);
        }
    }

    window.update();
}

void Game::update(float deltaTime) {
    entityManager.update(deltaTime);
}

void Game::render() {
    window.beginDraw();
    entityManager.render(*window.getRenderWindow());
    window.endDraw();
}