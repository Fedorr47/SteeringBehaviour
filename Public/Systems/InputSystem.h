#pragma once

#include "BaseSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include "Components/Components.h"
#include "InputHandler.h"

class InputSystem : public BaseSystem
{
public:

    void SetFocusState(bool currentFocus)
    {
        IsInFocus = currentFocus;
    }

    InputSystem(float maxForce, float maxSpeed, const sf::RenderWindow& window, const InputHandler& inputHandler)
        : window(window), inputHandler(inputHandler) {}

    virtual void update(entt::registry& registry, float deltaTime) override
    {
        auto view = registry.view<VelocityComponent, ControlComponent, FollowComponent>();
        for (auto entity : view) {
            auto& velocity = view.get<VelocityComponent>(entity);
            auto& control = view.get<ControlComponent>(entity);
            auto& follow = view.get<FollowComponent>(entity);

            if (!IsInFocus) {
                velocity.val = { 0.0f, 0.0f };
                continue;
            }
  
            if (control.autoSwitch) {
                if (inputHandler.isKeyPressed(sf::Keyboard::Left) || inputHandler.isKeyPressed(sf::Keyboard::Right) ||
                    inputHandler.isKeyPressed(sf::Keyboard::Up) || inputHandler.isKeyPressed(sf::Keyboard::Down)) {
                    control.useMouseControl = false;
                }
                else {
                    sf::Vector2i mousePos = inputHandler.getMousePosition(window);
                    if (mousePos != lastMousePosition) {
                        control.useMouseControl = true;
                        sf::Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                        follow.endPos = target;
                    }
                }
            }

            // TODO: moove to control system
            if (!control.useMouseControl) {
                if (inputHandler.isKeyPressed(sf::Keyboard::Left))
                    velocity.val.x = -velocity.speed;
                else if (inputHandler.isKeyPressed(sf::Keyboard::Right))
                    velocity.val.x = velocity.speed;
                else
                    velocity.val.x = 0;

                if (inputHandler.isKeyPressed(sf::Keyboard::Up))
                    velocity.val.y = -velocity.speed;
                else if (inputHandler.isKeyPressed(sf::Keyboard::Down))
                    velocity.val.y = velocity.speed;
                else
                    velocity.val.y = 0;
            }
        }
    }

private:
    const sf::RenderWindow& window;
    const InputHandler& inputHandler;
    bool IsInFocus = true;
    sf::Vector2i lastMousePosition{ 0, 0 };
};
