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
	registry.emplace<ShapeComponent>(player, CreateSquare(sf::Color::Green, 25.0f, 25.0f));
	registry.emplace<ControlComponent>(player, false, false);

	entities.push_back(player);

	// Obstacels
	auto obstacle = entityManager.createEntity();
	registry.emplace<PositionComponent>(obstacle, sf::Vector2f(400.0f, 400.0f));
	registry.emplace<ObstacleComponent>(obstacle, 30.0f);
	registry.emplace<ShapeComponent>(obstacle, CreateSquare(sf::Color::Yellow, 25.0f, 25.0f));

	auto obstacle1 = entityManager.createEntity();
	registry.emplace<PositionComponent>(obstacle1, sf::Vector2f(600.0f, 400.0f));
	registry.emplace<ObstacleComponent>(obstacle1, 30.0f);
	registry.emplace<ShapeComponent>(obstacle1, CreateSquare(sf::Color::Cyan, 25.0f, 25.0f));


	auto obstacle2 = entityManager.createEntity();
	registry.emplace<PositionComponent>(obstacle2, sf::Vector2f(400.0f, 600.0f));
	registry.emplace<ObstacleComponent>(obstacle2, 30.0f);
	registry.emplace<ShapeComponent>(obstacle2, CreateSquare(sf::Color::White, 25.0f, 25.0f));

	entities.push_back(obstacle);

	// Enemies
	
	auto Wnaderer = registry.create();

	registry.emplace<PositionComponent>(Wnaderer, sf::Vector2f(200.0f, 200.0f));
	registry.emplace<VelocityComponent>(Wnaderer, sf::Vector2f(0.0f, -10.0f), 5.0f, 5.0f);
	registry.emplace<MassComponent>(Wnaderer, 10.0f);

	registry.emplace<ShapeComponent>(Wnaderer, CreateTriangle(sf::Color::Red, 20.0f, 25.0f));

	registry.emplace<ChasingComponent>(
		Wnaderer
	);
	registry.get<ChasingComponent>(Wnaderer).Behaviors.push_back(std::make_shared<WanderBehavior>(
		10.0f,
		WanderRanges(100.0f, 100.0f),
		1000.0f,
		100.0f,
		45.0f));

	entities.push_back(Wnaderer);
	

	auto Pursuiter = registry.create();

	registry.emplace<PositionComponent>(Pursuiter, sf::Vector2f(250.0f, 250.0f));
	registry.emplace<VelocityComponent>(Pursuiter, sf::Vector2f(0.0f, 0.0f), 100.0f, 100.0f);
	registry.emplace<MassComponent>(Pursuiter, 2.0f);
	registry.emplace<AvoidanceComponent>(Pursuiter, 200.0f, 50.0f);

	registry.emplace<ShapeComponent>(Pursuiter, CreateTriangle(sf::Color::Red, 20.0f, 25.0f));

	registry.emplace<ChasingComponent>(
		Pursuiter
	);

	registry.get<ChasingComponent>(Pursuiter).Behaviors.push_back(std::make_shared<PursuitBehavior>(
		player,
		7.0f));

	registry.get<ChasingComponent>(Pursuiter).Behaviors.push_back(std::make_shared<EvadeBehavior>(
		Wnaderer,
		150.0f));


	entities.push_back(Pursuiter);

	auto Follower = registry.create();

	registry.emplace<PositionComponent>(Follower, sf::Vector2f(250.0f, 250.0f));
	registry.emplace<VelocityComponent>(Follower, sf::Vector2f(0.0f, 0.0f), 100.0f, 100.0f);
	registry.emplace<MassComponent>(Follower, 2.0f);
	registry.emplace<ShapeComponent>(Follower, CreateTriangle(sf::Color::Green, 20.0f, 25.0f));

	PathComponent path({
		sf::Vector2f(400.0f, 400.0f),
		sf::Vector2f(600.0f, 400.0f),
		sf::Vector2f(400.0f, 600.0f),
		sf::Vector2f(200.0f, 100.0f),
		sf::Vector2f(800.0f, 650.0f) });
	path.distanceToChangeNode = 25.0f;
	registry.emplace<PathComponent>(Follower, path);
}

sf::ConvexShape ObjectManager::CreateSquare(sf::Color color, float width, float height)
{
	sf::ConvexShape square;
	square.setPointCount(4);

	square.setPoint(0, sf::Vector2f(0.0f, 0.0f));
	square.setPoint(1, sf::Vector2f(width, 0.0f));
	square.setPoint(2, sf::Vector2f(width, height));
	square.setPoint(3, sf::Vector2f(0.0f, height));
	square.setFillColor(color);
	square.setOrigin(width / 2, height / 2);

	return square;
}

sf::ConvexShape ObjectManager::CreateTriangle(sf::Color color, float base, float height)
{
	sf::ConvexShape triangle;
	triangle.setPointCount(3);

	/*
	float L = 25.0f;
	float height = L * std::sin(75.0 * std::numbers::pi / 180.0);
	float base = 2 * L * std::cos(75.0 * std::numbers::pi / 180.0);
	*/

	triangle.setPoint(0, sf::Vector2f(base / 2.0f, 0.0f));
	triangle.setPoint(1, sf::Vector2f(base, height));
	triangle.setPoint(2, sf::Vector2f(0.0f, height));
	triangle.setFillColor(color);
	triangle.setOrigin(base / 2.0f, height / 2.0f);

	return triangle;
}