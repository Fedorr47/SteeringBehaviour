#pragma once

#include "BaseSystem.h"
#include "InputHandler.h"

class InputSystem : public BaseSystem
{
public:

    void SetFocusState(bool currentFocus)
    {
        IsInFocus = currentFocus;
    }

    InputSystem(
        entt::registry& registry,
        float maxForce, 
        float maxSpeed, 
        const sf::RenderWindow& window, 
        const InputHandler& inputHandler) : 
        BaseSystem(registry),
        window(window), 
        inputHandler(inputHandler) {}

    virtual void update(float deltaTime) override;

private:
    const sf::RenderWindow& window;
    const InputHandler& inputHandler;
    bool IsInFocus = true;
    sf::Vector2i lastMousePosition{ 0, 0 };
};
