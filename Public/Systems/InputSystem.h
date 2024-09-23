#pragma once
#include <entt/entt.hpp>
#include "Components/Components.h"
#include <SFML/Window/Keyboard.hpp>

class InputSystem
{
public:
    void update(entt::registry& registry, float deltaTime)
    {
        auto view = registry.view<VelocityComponent>();
        for (auto entity : view)
        {
            auto& velocity = view.get<VelocityComponent>(entity);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                velocity.velocity.x = -1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                velocity.velocity.x = 1;
            else
                velocity.velocity.x = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                velocity.velocity.y = -1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                velocity.velocity.y = 1;
            else
                velocity.velocity.y = 0;
        }
    }
};
