#include "Systems/FlockSystem.h"
#include "Utils/Utils.h"

void FlockSystem::update(float deltaTime)
{
    auto view = registry.view<FlockComponent, VelocityComponent, PositionComponent>();
	for (auto entity : view) {
		PositionComponent& position = view.get<PositionComponent>(entity);
		VelocityComponent& velocity = view.get<VelocityComponent>(entity);
		FlockComponent& flock = view.get<FlockComponent>(entity);

		if (flock.actor->role == FlockRole::Follower)
		{
			FlockFollower* follower = static_cast<FlockFollower*>(flock.actor.get());
			auto& leaderPosition = registry.get<PositionComponent>(follower->leader);

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
				//force = force + evade(leader);
			}
			else
			{
				registry.get<ChasingComponent>(flock.actor->id).Behaviors[0] = follower->arriveBehavior;
			}
			velocity.steering += separation();
		}
	}
}

sf::Vector2f FlockSystem::separation()
{
	sf::Vector2f force;
	int neighborCount = 0;

	/*/
	for (var i : int = 0; i < Game.instance.boids.length; i++) {
		var b : Boid = Game.instance.boids[i];
		if (b != this && distance(b, this) <= SEPARATION_RADIUS) {
			force.x += b.position.x - this.position.x;
			force.y += b.position.y - this.position.y;
			neighborCount++;
		}
	}

	if (neighborCount != 0) {
		force.x /= neighborCount;
		force.y /= neighborCount;
		force *= -1;
	}

	normalize(force);
	force *= MAX_SEPARATION;
	*/

	return force;
}

void FlockSystem::init()
{
	auto view = registry.view<FlockComponent, VelocityComponent, PositionComponent>();
	for (auto entity : view) {
		PositionComponent& position = view.get<PositionComponent>(entity);
		VelocityComponent& velocity = view.get<VelocityComponent>(entity);
		FlockComponent& flock = view.get<FlockComponent>(entity);

		if (flock.actor->role == FlockRole::Follower)
		{
			FlockFollower* follower = static_cast<FlockFollower*>(flock.actor.get());
			registry.emplace<ChasingComponent>(
				flock.actor->id
			);
			follower->evadeBehavior = std::make_shared<EvadeBehavior>(follower->leader, flock.leaderBehindDist+1);
			follower->arriveBehavior = std::make_shared<PursuitBehavior>(follower->leader, flock.leaderBehindDist-1);
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
