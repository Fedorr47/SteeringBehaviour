#pragma once

#include "BaseSystem.h"
#include "Components/Components.h"

class ShapeSystem : public BaseSystem
{
public:
    ShapeSystem(entt::registry& registry) :
        BaseSystem(registry)
    {}

    virtual void update(float deltaTime) override;
};