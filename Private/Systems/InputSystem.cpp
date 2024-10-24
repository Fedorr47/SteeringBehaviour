#include "Systems/InputSystem.h"

#include <SFML/Window/Keyboard.hpp>
#include "Components/Components.h"

void InputSystem::update(float deltaTime)
{
    auto view = registry.view<VelocityComponent, ControlComponent>();
    for (auto entity : view) {
        auto& velocity = view.get<VelocityComponent>(entity);
        auto& control = view.get<ControlComponent>(entity);

        if (!IsInFocus) {
            velocity.velocity = { 0.0f, 0.0f };
            continue;
        }

        if (control.autoSwitch) 
        {
            if (inputHandler.isKeyPressed(sf::Keyboard::Left) || inputHandler.isKeyPressed(sf::Keyboard::Right) ||
                inputHandler.isKeyPressed(sf::Keyboard::Up) || inputHandler.isKeyPressed(sf::Keyboard::Down)) {
                control.useMouseControl = false;
            }
            else 
            {
                sf::Vector2i mousePos = inputHandler.getMousePosition(window);
                if (mousePos != lastMousePosition) 
                {
                    control.useMouseControl = true;
                    sf::Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                }
            }
        }

        // TODO: moove to control system
        if (!control.useMouseControl) 
        {
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
