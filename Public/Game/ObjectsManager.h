#pragma once
#include <vector>
#include <ThirdParty/entt/entt.hpp>
#include "EntityManager/EntityManager.h"

class ObjectManager
{
public:
	void initObjects(EntityManager& entityManager, std::vector<entt::entity>& entities);
	sf::ConvexShape CreateSquare(sf::Color color, float width, float height);
	sf::ConvexShape CreateTriangle(sf::Color color, float base, float height);
};