#pragma once

#include "BaseSystem.h"
#include "Components/Components.h"

struct VelocityComponent;
struct PositionComponent;
struct CollisionComponent;

class CollisionSystem : public BaseSystem
{
public:
	CollisionSystem(entt::registry& registry) :
		BaseSystem(registry)
	{}
	sf::Vector2f calculateNormal(
		const PositionComponent& positionA,
		const PositionComponent& positionB);
	sf::Vector2f calculateSlidingVelocity(const sf::Vector2f& velocity, const sf::Vector2f& normal);
	void correctPosition(PositionComponent& positionA, const sf::FloatRect& boundsA, const sf::FloatRect& boundsB);
	void handleCollision(
		VelocityComponent& velocityA,
		PositionComponent& positionA,
		PositionComponent& positionB,
		const sf::FloatRect& boundsA,
		const sf::FloatRect& boundsB);
	virtual void update(float deltaTime) override;
};
