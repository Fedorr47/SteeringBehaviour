#include "Systems/CollisionSystem.h"
#include "Utils/Utils.h"

sf::Vector2f CollisionSystem::calculateNormal(
	const PositionComponent& positionA,
	const PositionComponent& positionB)
{
	sf::Vector2f diff = positionA.position - positionB.position;

	if (std::abs(diff.x) > std::abs(diff.y)) {
		return sf::Vector2f((diff.x > 0) ? 1.0f : -1.0f, 0.0f);
	}
	else {
		return sf::Vector2f(0.0f, (diff.y > 0) ? 1.0f : -1.0f);
	}
}

sf::Vector2f CollisionSystem::calculateSlidingVelocity(const sf::Vector2f& velocity, const sf::Vector2f& normal) {
	float dotProduct = velocity.x * normal.x + velocity.y * normal.y;

	sf::Vector2f normalComponent = dotProduct * normal;
	sf::Vector2f tangentialVelocity = velocity - normalComponent;

	float originalSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	sf::Vector2f newVelocity = normalize(tangentialVelocity) * originalSpeed;

	return newVelocity;
}


void CollisionSystem::correctPosition(
	PositionComponent& positionA,
	const sf::FloatRect& boundsA,
	const sf::FloatRect& boundsB)
{
	float overlapLeft = (boundsA.left + boundsA.width) - boundsB.left;
	float overlapRight = (boundsB.left + boundsB.width) - boundsA.left;
	float overlapTop = (boundsA.top + boundsA.height) - boundsB.top;
	float overlapBottom = (boundsB.top + boundsB.height) - boundsA.top;

	if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {
		positionA.position.x -= overlapLeft;
	}
	else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom) {
		positionA.position.x += overlapRight;
	}
	else if (overlapTop < overlapBottom) {
		positionA.position.y -= overlapTop;
	}
	else {
		positionA.position.y += overlapBottom;
	}
}

void CollisionSystem::handleCollision(
	VelocityComponent& velocityA,
	PositionComponent& positionA,
	PositionComponent& positionB,
	const sf::FloatRect& boundsA,
	const sf::FloatRect& boundsB)
{
	sf::Vector2f normal = calculateNormal(positionA, positionB);
	velocityA.velocity = calculateSlidingVelocity(velocityA.velocity, normal);
	correctPosition(positionA, boundsA, boundsB);
}

void CollisionSystem::update(float deltaTime)
{
	auto view = registry.view<ShapeComponent, PositionComponent>();
	for (auto entityA : view) 
	{
		PositionComponent& positionA = view.get<PositionComponent>(entityA);
		auto& shapeA = view.get<ShapeComponent>(entityA).shape;

		for (auto entityB : view) 
		{
			if (entityA == entityB) continue;

			auto& positionB = view.get<PositionComponent>(entityB);
			auto& shapeB = view.get<ShapeComponent>(entityB).shape;

			if (shapeA.getGlobalBounds().intersects(shapeB.getGlobalBounds()))
			{
				if (auto* velocityA = registry.try_get<VelocityComponent>(entityA)) {
					handleCollision(*velocityA, positionA, positionB, shapeA.getGlobalBounds(), shapeB.getGlobalBounds());
				}
			}
		}
	}
}
