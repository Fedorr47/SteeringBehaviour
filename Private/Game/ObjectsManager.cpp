#include "Game/ObjectsManager.h"
#include "EntityManager/EntityManager.h"
#include "Utils/Utils.h"

void ObjectManager::initObjects(EntityManager& entityManager, std::vector<entt::entity>& entities)
{
	// Player
	auto& registry = entityManager.getRegistry();
	auto player = entityManager.createEntity();
	registry.emplace<PositionComponent>(player, sf::Vector2f(375.0f, 275.0f));
	registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 200.0f, 200.0f);
	registry.emplace<MassComponent>(player, 100.0f);

	sf::ConvexShape square;
	square.setPointCount(4);

	square.setPoint(0, sf::Vector2f(25.0f, 25.0f));
	square.setPoint(1, sf::Vector2f(50.0f, 25.0f));
	square.setPoint(2, sf::Vector2f(50.0f, 50.0f));
	square.setPoint(3, sf::Vector2f(25.0f, 50.0f));
	square.setFillColor(sf::Color::Green);
	square.setOrigin(37.5f, 37.5f);

	registry.emplace<ShapeComponent>(player, square);
	registry.emplace<ControlComponent>(player, false, false);

	entities.push_back(player);

	// Enemy

	sf::ConvexShape triangle;
	triangle.setPointCount(3);

	float L = 25.0f;
	float height = L * std::sin(75.0 * std::numbers::pi / 180.0);
	float base = 2 * L * std::cos(75.0 * std::numbers::pi / 180.0);

	triangle.setPoint(0, sf::Vector2f(base / 2.0f, 0.0f));
	triangle.setPoint(1, sf::Vector2f(base, height));
	triangle.setPoint(2, sf::Vector2f(0.0f, height));
	triangle.setFillColor(sf::Color::Red);
	triangle.setOrigin(base / 2.0f, height / 2.0f);
	//

	
	auto Enemy = registry.create();

	registry.emplace<PositionComponent>(Enemy, sf::Vector2f(200.0f, 200.0f));
	registry.emplace<VelocityComponent>(Enemy, sf::Vector2f(0.0f, -10.0f), 5.0f, 5.0f);
	registry.emplace<MassComponent>(Enemy, 10.0f);

	registry.emplace<ShapeComponent>(Enemy, triangle);

	registry.emplace<ChasingComponent>(
		Enemy
	);
	registry.get<ChasingComponent>(Enemy).Behaviors.push_back(new WanderBehavior(
		registry.create(),
		10.0f,
		WanderRanges(100.0f, 100.0f),
		1000.0f,
		100.0f,
		45.0f));

	entities.push_back(Enemy);
	

	auto Enemy1 = registry.create();

	registry.emplace<PositionComponent>(Enemy1, sf::Vector2f(250.0f, 250.0f));
	registry.emplace<VelocityComponent>(Enemy1, sf::Vector2f(0.0f, 0.0f), 100.0f, 100.0f);
	registry.emplace<MassComponent>(Enemy1, 2.0f);

	registry.emplace<ShapeComponent>(Enemy1, triangle);

	registry.emplace<ChasingComponent>(
		Enemy1
	);

	registry.get<ChasingComponent>(Enemy1).Behaviors.push_back(new PursuitBehavior(
		player,
		7.0f));

	registry.get<ChasingComponent>(Enemy1).Behaviors.push_back(new EvadeBehavior(
		Enemy,
		150.0f));

	entities.push_back(Enemy1);

}