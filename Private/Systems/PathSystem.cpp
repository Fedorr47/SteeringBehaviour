#include "Systems/PathSystem.h"
#include "Utils/Utils.h"

void PathSystem::init()
{
    auto view = registry.view<PositionComponent, PathComponent>();
    for (auto entity : view) 
    {
        auto& path = view.get<PathComponent>(entity);
        auto& position = view.get<PositionComponent>(entity);

        for (auto& node : path.nodes)
        {
            if (node.id == entt::null)
            {
                auto stubNode = registry.create();
                registry.emplace<PositionComponent>(stubNode, node.position);
                node.id = stubNode;
            }
        }

        if (path.currentNode == -1)
        {
            int nodesCount = path.nodes.size();
            // Get the closest node
            float minDistance = std::numeric_limits<float>::max();
            for (int i = 0; i < nodesCount; ++i)
            {
                float newDistance = distance(path.nodes[i].position, position.position);
                if (minDistance > newDistance)
                {
                    minDistance = newDistance;
                    path.currentNode = i;
                }
            }

            path.pathBehavior = std::make_shared<PathBehavior>(path.nodes[path.currentNode].id, path.distanceToChangeNode);
            registry.emplace<ChasingComponent>(entity);
            registry.get<ChasingComponent>(entity).Behaviors.push_back(path.pathBehavior);
        }
    }
}

void PathSystem::update(float deltaTime)
{
    auto view = registry.view<PositionComponent, PathComponent>();

    for (auto entity : view) {
        auto& position = view.get<PositionComponent>(entity);
        auto& path = view.get<PathComponent>(entity);

        int nodesCount = path.nodes.size();
        
        if (path.currentNode != -1)
        {
            if (distance(position.position, path.nodes[path.currentNode].position) <= path.distanceToChangeNode) {

                path.currentNode = (path.currentNode + 1) % nodesCount;
                path.pathBehavior->object = path.nodes[path.currentNode].id;
            }
        }
    }
}
