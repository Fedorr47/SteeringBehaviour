#pragma once
#include "BaseSystem.h"
#include <SFML/Graphics.hpp>
#include "Components/Components.h"
#include <iostream>

class RenderSystem : public BaseSystem
{
public:

    RenderSystem(entt::registry& registry) :
        BaseSystem(registry)
    {}

    void render(sf::RenderWindow& window);

    virtual void update(float deltaTime) override
    {}
};
