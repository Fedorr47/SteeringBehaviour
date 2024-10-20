#include "Game/ObjectsManager.h"
#include "EntityManager/EntityManager.h"
#include "Utils/Utils.h"

// Test methods
void Wander_Pursuit_Path_Plyaer(EntityManager& entityManager, std::vector<entt::entity>& entities, ObjectManager& mngr)
{
	auto& registry = entityManager.getRegistry();
	auto player = entityManager.createEntity();

	registry.emplace<PositionComponent>(player, sf::Vector2f(375.0f, 275.0f));
	registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 200.0f, 200.0f);
	registry.emplace<MassComponent>(player, 100.0f);
	registry.emplace<ShapeComponent>(player, mngr.CreateSquare(sf::Color::Green, 25.0f, 25.0f));
	registry.emplace<ControlComponent>(player, false, false);

	entities.push_back(player);

	// Obstacels
	auto obstacle = entityManager.createEntity();
	registry.emplace<PositionComponent>(obstacle, sf::Vector2f(400.0f, 400.0f));
	registry.emplace<ObstacleComponent>(obstacle, 30.0f);
	registry.emplace<ShapeComponent>(obstacle, mngr.CreateSquare(sf::Color::Yellow, 25.0f, 25.0f));

	auto obstacle1 = entityManager.createEntity();
	registry.emplace<PositionComponent>(obstacle1, sf::Vector2f(600.0f, 400.0f));
	registry.emplace<ObstacleComponent>(obstacle1, 30.0f);
	registry.emplace<ShapeComponent>(obstacle1, mngr.CreateSquare(sf::Color::Cyan, 25.0f, 25.0f));


	auto obstacle2 = entityManager.createEntity();
	registry.emplace<PositionComponent>(obstacle2, sf::Vector2f(400.0f, 600.0f));
	registry.emplace<ObstacleComponent>(obstacle2, 30.0f);
	registry.emplace<ShapeComponent>(obstacle2, mngr.CreateSquare(sf::Color::White, 25.0f, 25.0f));

	entities.push_back(obstacle);

	// Enemies

	auto Wnaderer = registry.create();

	registry.emplace<PositionComponent>(Wnaderer, sf::Vector2f(200.0f, 200.0f));
	registry.emplace<VelocityComponent>(Wnaderer, sf::Vector2f(0.0f, -10.0f), 5.0f, 5.0f);
	registry.emplace<MassComponent>(Wnaderer, 10.0f);

	registry.emplace<ShapeComponent>(Wnaderer, mngr.CreateTriangle(sf::Color::Red, 20.0f, 25.0f));

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

	registry.emplace<ShapeComponent>(Pursuiter, mngr.CreateTriangle(sf::Color::Red, 20.0f, 25.0f));

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
	registry.emplace<ShapeComponent>(Follower, mngr.CreateTriangle(sf::Color::Green, 20.0f, 25.0f));

	PathComponent path({
		sf::Vector2f(400.0f, 400.0f),
		sf::Vector2f(600.0f, 400.0f),
		sf::Vector2f(400.0f, 600.0f),
		sf::Vector2f(200.0f, 100.0f),
		sf::Vector2f(800.0f, 650.0f) });
	path.distanceToChangeNode = 25.0f;
	registry.emplace<PathComponent>(Follower, path);
}

void Pursuit_Evade(EntityManager& entityManager, std::vector<entt::entity>& entities, ObjectManager& mngr)
{
	auto& registry = entityManager.getRegistry();
	auto player = entityManager.createEntity();

	registry.emplace<PositionComponent>(player, sf::Vector2f(375.0f, 275.0f));
	registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 200.0f, 200.0f);
	registry.emplace<MassComponent>(player, 100.0f);
	registry.emplace<ShapeComponent>(player, mngr.CreateSquare(sf::Color::Green, 25.0f, 25.0f));
	registry.emplace<ControlComponent>(player, false, false);

	entities.push_back(player);

	auto Pursuiter = registry.create();

	registry.emplace<PositionComponent>(Pursuiter, sf::Vector2f(250.0f, 250.0f));
	registry.emplace<VelocityComponent>(Pursuiter, sf::Vector2f(0.0f, 0.0f), 100.0f, 100.0f);
	registry.emplace<MassComponent>(Pursuiter, 2.0f);
	registry.emplace<AvoidanceComponent>(Pursuiter, 200.0f, 50.0f);

	registry.emplace<ShapeComponent>(Pursuiter, mngr.CreateTriangle(sf::Color::Red, 20.0f, 25.0f));

	registry.emplace<ChasingComponent>(
		Pursuiter
	);

	registry.get<ChasingComponent>(Pursuiter).Behaviors.push_back(std::make_shared<PursuitBehavior>(
		player,
		149.0f));

	registry.get<ChasingComponent>(Pursuiter).Behaviors.push_back(std::make_shared<EvadeBehavior>(
		player,
		151.0f));

	entities.push_back(Pursuiter);
}

void Flock(EntityManager& entityManager, std::vector<entt::entity>& entities, ObjectManager& mngr)
{
	auto& registry = entityManager.getRegistry();
	auto player = entityManager.createEntity();

	registry.emplace<PositionComponent>(player, sf::Vector2f(600.0f, 400.0f));
	registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 300.0f, 300.0f);
	registry.emplace<MassComponent>(player, 100.0f);
	auto shape = mngr.CreateSquare(sf::Color::Green, 25.0f, 25.0f);
	registry.emplace<ShapeComponent>(player, shape);
	registry.emplace<ControlComponent>(player, false, false);
	auto leaderPtr = std::make_shared<FlockLeader>(player);
	registry.emplace<FlockComponent>(player, leaderPtr);

	entities.push_back(player);

	/// Flock Actors
	std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Yellow, sf::Color::Blue, sf::Color::Magenta };
	float x = 400.0f;
	for (size_t i = 0; i < 2; ++i) {
		auto entity = registry.create();
		x += 30.0f;
		auto pos = sf::Vector2f(x, 450.0f);
		registry.emplace<PositionComponent>(entity, pos);
		registry.emplace<VelocityComponent>(entity, sf::Vector2f(0.0f, 0.0f), 200.0f, 200.0f);
		registry.emplace<MassComponent>(entity, 5.0f);
		shape = mngr.CreateTriangle(colors[i % colors.size()], 20.0f, 25.0f);
		registry.emplace<ShapeComponent>(entity, shape);

		auto followerPtr = std::make_shared<FlockFollower>(entity, player, leaderPtr);
		registry.emplace<FlockComponent>(entity, followerPtr, 80.0f, 30.0f, 30.0f, 40.0f);

		leaderPtr->followers.push_back(followerPtr);
		entities.push_back(entity);
	}
	/// End Flock Actors
}


void Collide(EntityManager& entityManager, std::vector<entt::entity>& entities, ObjectManager& mngr)
{
	auto& registry = entityManager.getRegistry();
	auto player = entityManager.createEntity();

	registry.emplace<PositionComponent>(player, sf::Vector2f(600.0f, 400.0f));
	registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 300.0f, 300.0f);
	registry.emplace<MassComponent>(player, 100.0f);
	auto shape = mngr.CreateSquare(sf::Color::Green, 25.0f, 25.0f);
	registry.emplace<ShapeComponent>(player, shape);
	registry.emplace<ControlComponent>(player, false, false);
	auto leaderPtr = std::make_shared<FlockLeader>(player);

	entities.push_back(player);

	auto obstacle = entityManager.createEntity();
	registry.emplace<PositionComponent>(obstacle, sf::Vector2f(400.0f, 400.0f));
	registry.emplace<ObstacleComponent>(obstacle, 30.0f);
	shape = mngr.CreateSquare(sf::Color::Yellow, 25.0f, 25.0f);
	registry.emplace<ShapeComponent>(obstacle, shape);

	entities.push_back(obstacle);
}
// end test methods

void ObjectManager::initObjects(EntityManager& entityManager, std::vector<entt::entity>& entities)
{
	Flock(entityManager, entities, *this); // TODO: need to replace to file reading  
	//Collide(entityManager, entities, *this);
	entityManager.init();
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

