#include "Systems/FollowSystem.h"

void FollowSystem::ManageFollow(ManageParams& params)
{
	FollowDebugInfo info;

	switch (params.chasComp->type)
	{
	case MoveBehaviourType::Seek:
		Seek(params);
		break;
	case MoveBehaviourType::Flee:
		Flee(params);
		break;
	case MoveBehaviourType::Wander:
		Wander(params);
		info.wanderAngle = static_cast<WanderBehavior*>(params.chasComp->Behavior)->wanderAngle;
		break;
	default:
		break;
	}

	info.entityID = params.entity_id;
	info.position = params.posComp->position;
	info.velocity = params.velComp->velocity;
	info.distanceToTarget = params.distance;
	debugInfo->chasingEntities[params.entity_id] = info;
}

void FollowSystem::GetVelocity(ManageParams& params)
{
	auto& target_position = params.reg->get<PositionComponent>(params.chasComp->Behavior->object);
	auto desired_velocity = target_position.position - params.posComp->position;
	float distance = getLength(desired_velocity);
	float radius = params.chasComp->Behavior->slowingRadius;
	float max_speed = params.velComp->MaxSpeed;

	params.distance = distance;

	if (distance < radius) {
		desired_velocity = normalize(desired_velocity) * max_speed * (distance / radius);
	}
	else {
		desired_velocity = normalize(desired_velocity) * max_speed;
	}

	auto steering = desired_velocity - params.velComp->velocity;
	params.velComp->velocity += steering;
}

void FollowSystem::Wander(ManageParams& params) 
{
	WanderBehavior* wanderBehaviour = static_cast<WanderBehavior*>(params.chasComp->Behavior);
	if (wanderBehaviour != nullptr)
	{
		static sf::Clock clock;
		static std::random_device dev;
		static std::mt19937 gen(dev()); 

		auto now = clock.getElapsedTime().asMilliseconds();
		auto& targetPosition = params.reg->get<PositionComponent>(wanderBehaviour->object);

		if (now >= wanderBehaviour->nextDecisionTime)
		{
			wanderBehaviour->nextDecisionTime = now + wanderBehaviour->timeWaiting;
			sf::Vector2f circleCenter = normalize(params.velComp->velocity) * wanderBehaviour->circleDistance;

			sf::Vector2f displacement(0, -1);
			displacement *= wanderBehaviour->circleDistance;

			setAngle(displacement, wanderBehaviour->wanderAngle);

			wanderBehaviour->wanderAngle += std::uniform_real_distribution<float>(-wanderBehaviour->angleChange / 2, wanderBehaviour->angleChange / 2)(gen);
			wanderBehaviour->wanderAngle = fmod(wanderBehaviour->wanderAngle, 360.0f);
			if (wanderBehaviour->wanderAngle > 180.0f) {
				wanderBehaviour->wanderAngle -= 360.0f;
			}
			else if (wanderBehaviour->wanderAngle < -180.0f) {
				wanderBehaviour->wanderAngle += 360.0f;
			}

			sf::Vector2f wanderForce = circleCenter + displacement;

			params.velComp->velocity = wanderForce;
		}
	}
}

void FollowSystem::Seek(ManageParams& params)
{
	GetVelocity(params);
}

void FollowSystem::Flee(ManageParams& params)
{
	GetVelocity(params);
	params.velComp->velocity *= -1;
	
}
