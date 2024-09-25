#pragma once
#include <ThirdParty/entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "Components/Components.h"

class RenderSystem
{
public:
    void render(entt::registry& registry, sf::RenderWindow& window)
    {
        auto view = registry.view<PositionComponent, ShapeComponent>();
        for (auto entity : view)
        {
            auto& position = view.get<PositionComponent>(entity);
            auto& shape = view.get<ShapeComponent>(entity);

            shape.shape.setPosition(position.position);

            window.draw(shape.shape);
        }
    }
};
