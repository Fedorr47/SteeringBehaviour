#include "Systems/CollisionSystem.h"
#include "Utils/Utils.h"

constexpr float correctionDist = 0.1f;

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
	if (positionA.isCorrecting) {
		return;
	}

	float overlapLeft = (boundsA.left + boundsA.width) - boundsB.left;
	float overlapRight = (boundsB.left + boundsB.width) - boundsA.left;
	float overlapTop = (boundsA.top + boundsA.height) - boundsB.top;
	float overlapBottom = (boundsB.top + boundsB.height) - boundsA.top;

	if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {
		positionA.position.x -= overlapLeft - correctionDist;
	}
	else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom) {
		positionA.position.x += overlapRight + correctionDist;
	}
	else if (overlapTop < overlapBottom) {
		positionA.position.y -= overlapTop - correctionDist;
	}
	else {
		positionA.position.y += overlapBottom + correctionDist;
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
	float dotProduct = velocityA.velocity.x * normal.x + velocityA.velocity.y * normal.y;

	if (dotProduct < 0.0f) {
		velocityA.velocity = calculateSlidingVelocity(velocityA.velocity, normal);
		correctPosition(positionA, boundsA, boundsB);

		positionA.isCorrecting = true;
	}
	else {
		positionA.isCorrecting = false;
	}
}

void CollisionSystem::resolveCollision(
	entt::entity entityA,
	entt::entity entityB,
	VelocityComponent& velocityA, 
	VelocityComponent& velocityB,
	PositionComponent& positionA,
	PositionComponent& positionB,
	ShapeComponent& shapeA,
	ShapeComponent& shapeB)
{
	sf::Vector2f normal = calculateNormal(positionA, positionB);
	sf::Vector2f rv = velocityB.velocity - velocityA.velocity;
	float velAlongNormal = dotProduct(rv, normal);

	if (velAlongNormal > 0)
		return;

	float e = std::min(shapeA.restitution, shapeB.restitution);
	// Calculate impulse scalar 
	float j = -(1 + e) * velAlongNormal;

	auto* massA = registry.try_get<MassComponent>(entityA);
	auto* massB = registry.try_get<MassComponent>(entityB);

	j /= 1 / massA->invMass + 1 / massB->invMass;

	sf::Vector2f impulse = j * normal;
	velocityA.velocity -= massA->invMass * impulse;
	velocityB.velocity += massB->invMass * impulse;
}

void CollisionSystem::PositionalCorrection(
	entt::entity entityA,
	entt::entity entityB,
	PositionComponent& positionA,
	PositionComponent& positionB
)
{
	auto* massA = registry.try_get<MassComponent>(entityA);
	auto* massB = registry.try_get<MassComponent>(entityB);
	const float percent = 0.2f;
	const float slop = 0.01f;
	//sf::Vector2f correction = (std::max(penetration - slop, 0.0f) / (massA->invMass + massB->invMass))* percent * n;
	positionA.position -= massA->invMass * correction;
	positionB.position += massB->invMass * correction;
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
				auto* velocityA = registry.try_get<VelocityComponent>(entityA);
				auto* velocityB = registry.try_get<VelocityComponent>(entityB);
				if (velocityA != nullptr && velocityB == nullptr) {
					handleCollision(*velocityA, positionA, positionB, shapeA.getGlobalBounds(), shapeB.getGlobalBounds());
				}
				else if (velocityA != nullptr && velocityB != nullptr)
				{

				}
			}
		}
	}
}
