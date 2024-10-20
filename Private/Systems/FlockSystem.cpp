#include "Systems/FlockSystem.h"
#include "Utils/Utils.h"

void FlockSystem::update(float deltaTime)
{
    auto view = registry.view<FlockComponent, VelocityComponent, PositionComponent>();
	for (auto entity : view) 
	{
		PositionComponent& position = view.get<PositionComponent>(entity);
		VelocityComponent& velocity = view.get<VelocityComponent>(entity);
		FlockComponent& flock = view.get<FlockComponent>(entity);

		if (flock.actor->role == FlockRole::Follower)
		{
			FlockFollower* follower = static_cast<FlockFollower*>(flock.actor.get());
			auto& leaderPosition = registry.get<PositionComponent>(follower->leaderId);

			sf::Vector2f tv = velocity.velocity;
			sf::Vector2f force;

			normalize(tv);
			tv *= flock.leaderBehindDist;
			sf::Vector2f ahead = leaderPosition.position + tv;
			
			tv *= -1;
			sf::Vector2f behind = leaderPosition.position + tv;

			if (isOnLeaderSight(ahead, leaderPosition.position, position.position, flock.leaderSightRadius))
			{
				registry.get<ChasingComponent>(flock.actor->id).Behaviors[0] = follower->evadeBehavior;
			}
			else
			{
				registry.get<ChasingComponent>(flock.actor->id).Behaviors[0] = follower->arriveBehavior;
			}
			
			FlockLeader* leaderPtr = follower->leaderPtr.lock().get();

			velocity.steering += separation(
				flock,
				leaderPtr,
				follower,
				position.position);
		}
	}
}

sf::Vector2f FlockSystem::separation(
	FlockComponent& flockComp,
	const FlockLeader* leader,
	FlockFollower* follower,
	sf::Vector2f followerPos)
{
	sf::Vector2f force;
	int neighborCount = 0;

	for (auto anotherFollower : leader->followers) {
		auto& anotherFollowerPos = registry.get<PositionComponent>(anotherFollower->id).position;
		if (follower->id != anotherFollower->id && distance(anotherFollowerPos, followerPos) <= flockComp.separationRadius) {
			force.x += anotherFollowerPos.x - followerPos.x;
			force.y += anotherFollowerPos.y - followerPos.y;
			neighborCount++;
		}
	}

	if (neighborCount != 0) {
		force.x /= neighborCount;
		force.y /= neighborCount;
		force *= -1;
	}

	normalize(force);
	force *= flockComp.maxSeparation;

	return force;
}

void FlockSystem::init()
{
	auto view = registry.view<FlockComponent, VelocityComponent, PositionComponent>();
	for (auto entity : view) 
	{
		PositionComponent& position = view.get<PositionComponent>(entity);
		VelocityComponent& velocity = view.get<VelocityComponent>(entity);
		FlockComponent& flock = view.get<FlockComponent>(entity);

		if (flock.actor->role == FlockRole::Follower)
		{
			FlockFollower* follower = static_cast<FlockFollower*>(flock.actor.get());
			registry.emplace<ChasingComponent>(
				flock.actor->id
			);
			follower->evadeBehavior = std::make_shared<EvadeBehavior>(follower->leaderId, flock.leaderBehindDist+1);
			follower->arriveBehavior = std::make_shared<PursuitBehavior>(follower->leaderId, flock.leaderBehindDist-1);
			follower->actualBehavior = follower->arriveBehavior;

			registry.get<ChasingComponent>(flock.actor->id).Behaviors.push_back(follower->actualBehavior);
		}
	}
}

bool FlockSystem::isOnLeaderSight(
	sf::Vector2f leaderAhead, 
	sf::Vector2f leaderPosition,
	sf::Vector2f followerPosition,
	float leaderSightRadius)
{
	return distance(leaderAhead, followerPosition) <= leaderSightRadius || 
		distance(leaderPosition, followerPosition) <= leaderSightRadius;
}
