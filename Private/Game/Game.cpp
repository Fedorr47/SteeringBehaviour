#include "Game/Game.h"
#include "ThirdParty/entt/entt.hpp"
#include "Player/Player.h"
#include "Components/Components.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "ThirdParty/imgui/imgui-SFML.h"
#include "ThirdParty/imgui/imgui.h"
#include <iostream>

const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);

Game::Game() : 
    window("Steering Behaviour with EntityManager", { 800, 600 }),
    settings{ 500.0f, 200.0f, *window.getRenderWindow(), true },
    entityManager(settings, inputHandler)
{
    active_entity.push_back(entityManager.createPlayer(false));
    active_entity.push_back(entityManager.createNonPlayer());

    ImGui::SFML::Init(*window.getRenderWindow());
}

Game::~Game()
{
    ImGui::SFML::Shutdown();
}

void Game::run() 
{
    sf::Time deltaTime;
    sf::Clock fpsUpdateClock;

    while (window.isOpen()) {
        processEvents();

        deltaTime += clock.restart();
        fps = 1.0f / deltaTime.asSeconds();

        if (fpsUpdateClock.getElapsedTime().asSeconds() >= 0.5) {
            currentFPS = fps;
            fpsUpdateClock.restart(); 
        }

        while (deltaTime > TimePerFrame) {
            deltaTime -= TimePerFrame;
            update(TimePerFrame);
        }

        ImGui::SFML::Update(*window.getRenderWindow(), deltaTime);
       
        render(deltaTime);
    }
}

void Game::processEvents() {
    sf::Event event; 
    while (window.getRenderWindow()->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(*window.getRenderWindow(), event);
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

void Game::update(sf::Time deltaTime) {
    entityManager.update(deltaTime.asSeconds());
}

void Game::render(sf::Time deltaTime) {
    window.beginDraw();

    entityManager.render(*window.getRenderWindow());
    /***/
    ImGui::Begin("Debug Info");
    ImGui::Text("FPS: %.1f", currentFPS);
    ImGui::End();

    ImGui::SFML::Render(*window.getRenderWindow());
    /****/
    window.endDraw();
}