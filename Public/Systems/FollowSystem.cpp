#include "FollowSystem.h"

void FollowSystem::ManageFollow(ManageParams& params)
{
	switch (params.chasComp->type)
	{
	case MoveBehaviourType::Seek:
		Seek(params);
		break;
	case MoveBehaviourType::Flee:
		Flee(params);
		break;
	default:
		break;
	}

	FollowDebugInfo info;
	info.entityID = params.entity_id;
	info.position = params.posComp->position;
	info.velocity = params.velComp->velocity;
	info.distanceToTarget = params.distance;
	debugInfo->chasingEntities[params.entity_id] = info;
}

void FollowSystem::GetVelocity(ManageParams& params)
{
	auto& target_position = params.reg->get<PositionComponent>(params.chasComp->object);
	auto desired_velocity = target_position.position - params.posComp->position;
	float distance = getLength(desired_velocity);
	float radius = params.chasComp->slowingRadius;
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

void FollowSystem::Seek(ManageParams& params)
{
	GetVelocity(params);
}

void FollowSystem::Flee(ManageParams& params)
{
	GetVelocity(params);
	params.velComp->velocity *= -1;
}
