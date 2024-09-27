#pragma once
#include "BaseSystem.h"
#include <SFML/Graphics.hpp>
#include "Components/Components.h"

class RenderSystem : public BaseSystem
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

    virtual void update(entt::registry& registry, float deltaTime) override
    {}
};
