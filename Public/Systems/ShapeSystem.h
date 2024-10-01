#pragma once

#include "BaseSystem.h"
#include "Components/Components.h"

class ShapeSystem : public BaseSystem
{
public:
	virtual void update(entt::registry& registry, float deltaTime) override
	{
        auto view = registry.view<ShapeComponent, PositionComponent>();
        for (auto entity : view) {
            auto& shape = view.get<ShapeComponent>(entity);
            auto& position = view.get<PositionComponent>(entity);

            shape.shape.setRotation(position.angle);
        }
	}
};