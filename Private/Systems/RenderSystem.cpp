#include "Systems/RenderSystem.h"

void RenderSystem::render(sf::RenderWindow& window)
{
    class entt::basic_view<
        struct entt::get_t<
        class entt::basic_sigh_mixin<
        class entt::basic_storage<struct PositionComponent, enum entt::entity, class std::allocator<struct PositionComponent>, void>,
        class entt::basic_registry<enum entt::entity, class std::allocator<enum entt::entity> > >,
        class entt::basic_sigh_mixin<
        class entt::basic_storage<struct ShapeComponent, enum entt::entity, class std::allocator<struct ShapeComponent>, void>,
        class entt::basic_registry<enum entt::entity, class std::allocator<enum entt::entity> > > >,
        struct entt::exclude_t<>, void>
        view = registry.view<PositionComponent, ShapeComponent>();

    for (auto entity : view)
    {
        auto& position = view.get<PositionComponent>(entity);
        auto& shape = view.get<ShapeComponent>(entity);

        shape.shape.setPosition(position.position);

        window.draw(shape.shape);
    }
}
