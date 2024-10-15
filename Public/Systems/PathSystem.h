#pragma once

#include "BaseSystem.h"
#include "Components/Components.h"

class PathSystem : public BaseSystem
{
public:
    PathSystem(entt::registry& registry) :
        BaseSystem(registry)
    {}

    virtual void update(float deltaTime) override;
};