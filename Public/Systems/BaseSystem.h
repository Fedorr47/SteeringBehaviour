#pragma once
#include <ThirdParty/entt/entt.hpp>

class BaseSystem {
public:
    virtual void update(entt::registry& registry, float deltaTime) = 0;
};