#pragma once
#include <ThirdParty/entt/entt.hpp>
#include <SFML/Graphics.hpp>

class DebugInfo;

class BaseSystem {
public:
    BaseSystem(entt::registry& registry) :
        registry(registry)
    {}

    virtual void init() {};
    virtual void update(float deltaTime) = 0;
    std::shared_ptr<DebugInfo> debugInfo;

protected:
    entt::registry& registry;
   
};