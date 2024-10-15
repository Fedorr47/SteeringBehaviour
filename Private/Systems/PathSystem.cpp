#include "Systems/PathSystem.h"
#include "Utils/Utils.h"

// TODO: delete it and move path behavior to a proper Behavior class
void PathSystem::update(float deltaTime)
{
    auto view = registry.view<PositionComponent, PathComponent>();

    for (auto entity : view) {
        auto& position = view.get<PositionComponent>(entity);
        auto& path = view.get<PathComponent>(entity);

        int nodesCount = path.nodes.size();
        if (path.currentNode == -1)
        {
            // Get the closest node
            float minDistance = std::numeric_limits<float>::max();
            for (int i = 0; i < nodesCount; ++i)
            {
                float newDistance = distance(path.nodes[i], position.position);
                if (minDistance > newDistance)
                {
                    minDistance = newDistance;
                    path.currentNode = i;
                }
            }
        }
        if (distance(position.position, path.nodes[path.currentNode]) <= path.distanceToChangeNode) {
            path.currentNode = (path.currentNode + 1) % nodesCount;
        }
    }
}
