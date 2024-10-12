#pragma once
#include "Systems/BaseSystem.h"
#include "Systems/InputHandler.h"
#include "Systems/RenderSystem.h"
#include "Settings/GameSettings.h"


class EntityManager
{
public:
    EntityManager(const GameSettings& settings, const InputHandler& inputHandler, std::shared_ptr<DebugInfo> debugInfo);

    entt::entity createEntity();

    entt::entity createStub();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void SetFocusState(bool CurrentState);

    entt::registry& getRegistry() { return registry; }

private:
    entt::registry registry;

    std::vector<std::pair<std::string, std::unique_ptr<BaseSystem>>> Systems;
    std::unique_ptr<RenderSystem> RenderSys;
};
