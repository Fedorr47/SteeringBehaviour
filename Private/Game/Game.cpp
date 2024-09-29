﻿#include "Game/Game.h"
#include <iostream>
#include "Components/Components.h"
#include "ThirdParty/entt/entt.hpp"
#include "Player/Player.h"
#include "ThirdParty/imgui/imgui-SFML.h"
#include "ThirdParty/imgui/imgui.h"


const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);

Game::Game() :
    window("Steering Behaviour with EntityManager", { 800, 600 })
{
    debugInfo = DebugInfo::create();

    settings = std::unique_ptr<GameSettings>(new GameSettings(500.0f, 200.0f, *window.getRenderWindow(), true, 60));
    inputHandler = std::make_unique<GameInputHandler>();
    entityManager = std::unique_ptr<EntityManager>(new EntityManager(*settings.get(), *inputHandler.get(), debugInfo));

    // TODO(block): Create separate class to manage objects (builder pattern + reading from a file)
    int enemies_count = 1;
    auto player = entityManager->createPlayer(false);
    active_entity.push_back(player);

    for (int i = 0; i < enemies_count; ++i)
    {
        auto enemy = entityManager->createNonPlayer();
        active_entity.push_back(enemy);
        entityManager->getRegistry().emplace<ChasingComponent>(enemy, MoveBehaviourType::Seek, player, 45.0f); // TODO: add radius by object size
    }
    // END TODO(block)

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

        auto update_value = clock.restart();
        deltaTime += update_value;

        if (fpsUpdateClock.getElapsedTime().asSeconds() >= 0.5) {
            currentFPS = 1.0f / update_value.asSeconds();
            debugInfo->fps = currentFPS;
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
            entityManager->SetFocusState(false);
        }
        else if (event.type == sf::Event::GainedFocus) {
            entityManager->SetFocusState(true);
        }
    }

    window.update();
}

void Game::update(sf::Time deltaTime) {
    entityManager->update(deltaTime.asSeconds());
}

void Game::render(sf::Time deltaTime) {
    window.beginDraw();

    entityManager->render(*window.getRenderWindow());
    /***/
    ImGui::Begin("Debug Info");
    ImGui::Text("FPS: %.1f", debugInfo->fps);

    ImGui::Text("Chasing Entities:");
    for (const auto& [entity, FollowData] : debugInfo->chasingEntities) {
        ImGui::BulletText("Entity %d: \n\tPosition(%.2f, %.2f) \n\tVelocity(%.2f, %.2f) \n\tDistance to target(%.1f)",
            entity,
            FollowData.position.x, FollowData.position.y,
            FollowData.velocity.x, FollowData.velocity.y,
            FollowData.distanceToTarget);
    }

    ImGui::End();

    ImGui::SFML::Render(*window.getRenderWindow());
    /****/
    window.endDraw();
}