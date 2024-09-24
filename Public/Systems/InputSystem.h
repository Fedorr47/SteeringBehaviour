#pragma once

#include <entt/entt.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Components/Components.h"
#include "InputHandler.h"

inline sf::Vector2f truncate(const sf::Vector2f& vec, float max) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length > max) {
        return vec * (max / length);
    }
    return vec;
}

class InputSystem {
public:

    void SetFocusState(bool currentFocus)
    {
        IsInFocus = currentFocus;
    }

    InputSystem(float maxForce, float maxSpeed, const sf::RenderWindow& window, const InputHandler& inputHandler)
        : maxForce(maxForce), maxSpeed(maxSpeed), window(window), inputHandler(inputHandler) {}

    void update(entt::registry& registry, float deltaTime) {
        auto view = registry.view<VelocityComponent, ControlComponent, PositionComponent, MassComponent>();
        for (auto entity : view) {
            auto& velocity = view.get<VelocityComponent>(entity);
            auto& control = view.get<ControlComponent>(entity);
            auto& mass = view.get<MassComponent>(entity);
            auto& position = view.get<PositionComponent>(entity);

            if (!IsInFocus) {
                velocity.velocity = { 0.0f, 0.0f };
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
                    }
                    lastMousePosition = mousePos;
                }
            }

            if (control.useMouseControl) {
                sf::Vector2i mousePos = inputHandler.getMousePosition(window);
                sf::Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                float stopThreshold = 5.0f;
                float distanceToTarget = std::sqrt(std::pow(target.x - position.position.x, 2) +
                    std::pow(target.y - position.position.y, 2));

                if (distanceToTarget > stopThreshold) {
                    sf::Vector2f steering = target - position.position;
                    steering = truncate(steering, maxForce);
                    velocity.velocity = truncate(velocity.velocity + (steering / mass.mass), maxSpeed);
                }
                else {
                    velocity.velocity = { 0.0f, 0.0f };
                }
            }
            else {
                if (inputHandler.isKeyPressed(sf::Keyboard::Left))
                    velocity.velocity.x = -velocity.speed;
                else if (inputHandler.isKeyPressed(sf::Keyboard::Right))
                    velocity.velocity.x = velocity.speed;
                else
                    velocity.velocity.x = 0;

                if (inputHandler.isKeyPressed(sf::Keyboard::Up))
                    velocity.velocity.y = -velocity.speed;
                else if (inputHandler.isKeyPressed(sf::Keyboard::Down))
                    velocity.velocity.y = velocity.speed;
                else
                    velocity.velocity.y = 0;
            }
        }
    }

private:
    float maxForce;
    float maxSpeed;
    const sf::RenderWindow& window;
    const InputHandler& inputHandler;
    bool IsInFocus = true;
    sf::Vector2i lastMousePosition{ 0, 0 };
};
