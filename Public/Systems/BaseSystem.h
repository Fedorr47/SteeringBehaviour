#pragma once
#include <ThirdParty/entt/entt.hpp>

class DebugInfo;

class BaseSystem {
public:
    virtual void update(entt::registry& registry, float deltaTime) = 0;
    std::shared_ptr<DebugInfo> debugInfo;
};