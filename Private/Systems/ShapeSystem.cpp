#include "Systems/ShapeSystem.h"

void ShapeSystem::update(float deltaTime)
{
    class entt::basic_group<
        struct entt::owned_t<
        class entt::basic_sigh_mixin<
        class entt::basic_storage<struct ShapeComponent, enum entt::entity, class std::allocator<struct ShapeComponent>, void>,
        class entt::basic_registry<enum entt::entity, class std::allocator<enum entt::entity> > >,
        class entt::basic_sigh_mixin<
        class entt::basic_storage<struct PositionComponent, enum entt::entity, class std::allocator<struct PositionComponent>, void>,
        class entt::basic_registry<enum entt::entity, class std::allocator<enum entt::entity> > > >,
        struct entt::get_t<>,
        struct entt::exclude_t<> > group
        = registry.group<ShapeComponent, PositionComponent>();

    for (auto entity : group) {
        auto& shape = group.get<ShapeComponent>(entity);
        auto& position = group.get<PositionComponent>(entity);

        shape.shape.setRotation(position.angle);
    }
}
