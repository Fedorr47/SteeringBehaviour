#pragma once

#include "BaseSystem.h"
#include "Components/Components.h"

class FlockSystem : public BaseSystem
{
public:
	FlockSystem(entt::registry& registry) :
		BaseSystem(registry)
	{}

	virtual void update(float deltaTime) override;
	sf::Vector2f separation();
	virtual void init() override;
	bool isOnLeaderSight(
		sf::Vector2f leaderAhead,
		sf::Vector2f leaderPosition,
		sf::Vector2f followerPosition,
		float leaderSightRadius);
};
