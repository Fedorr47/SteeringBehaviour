#include "Systems/FollowSystem.h"

void FollowSystem::ManageFollow(ManageParams& params)
{
	params.velComp->steering = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f steerring;
	for (MovementBehavior* behavior : params.chasComp->Behaviors)
	{
		params.currentBehavior = behavior;
		switch (behavior->type)
		{
		case MoveBehaviourType::Seek:
			params.targetPos = params.reg->get<PositionComponent>(behavior->object).position;
			steerring = Seek(params);
			break;
		case MoveBehaviourType::Flee:
			params.targetPos = params.reg->get<PositionComponent>(behavior->object).position;
			steerring = Flee(params);
			break;
		case MoveBehaviourType::Wander:
			steerring = Wander(params);
			break;
		case MoveBehaviourType::Pursuit:
			steerring = Pursuit(params);
			break;
		case MoveBehaviourType::Evade:
			steerring = Evade(params);
			break;
		default:
			break;
		}

		params.velComp->steering += steerring;

		params.info.entityID = params.entityID;
		params.info.position = params.posComp->position;
		params.info.velocity = params.velComp->velocity;
		debugInfo->chasingEntities[params.info.entityID] = params.info;
	}
}

float randomFloat(float min, float max) {
	// Возвращает случайное число между min и max
	return min + (float(rand()) / float(RAND_MAX)) * (max - min);
}

sf::Vector2f FollowSystem::Wander(ManageParams& params)
{
	sf::Vector2f wanderForce;
	WanderBehavior* wanderBehaviour = static_cast<WanderBehavior*>(params.currentBehavior);
	if (wanderBehaviour != nullptr)
	{
		static sf::Clock clock;
		static std::random_device dev;
		static std::mt19937 gen(dev());
		static float wanderOrientation{0.0f};

		params.info.wanderAngle = wanderBehaviour->wanderAngle;

		auto now = clock.getElapsedTime().asMilliseconds();

		if (now >= wanderBehaviour->nextDecisionTime)
		{
			wanderBehaviour->nextDecisionTime = now + wanderBehaviour->timeWaiting;
			sf::Vector2f circleCenter = normalize(params.velComp->velocity) * wanderBehaviour->circleDistance;

			sf::Vector2f displacement(0, -1);
			displacement *= wanderBehaviour->circleDistance;

			wanderBehaviour->wanderAngle += randomFloat(-wanderBehaviour->angleChange, wanderBehaviour->angleChange);
			wanderBehaviour->wanderAngle = fmod(wanderBehaviour->wanderAngle, 360.0f);

			displacement = setAngle(displacement, wanderBehaviour->wanderAngle);

			wanderForce = circleCenter + displacement;
		}
	}
	return wanderForce;
}

void FollowSystem::PredictPostion(ManageParams& params)
{
	PursuitBehavior* pursuingBehaviour = static_cast<PursuitBehavior*>(params.currentBehavior);
	if (pursuingBehaviour != nullptr)
	{

		sf::Vector2f& targetPosition = params.reg->get<PositionComponent>(pursuingBehaviour->object).position;
		sf::Vector2f& targetVelocity = params.reg->get<VelocityComponent>(pursuingBehaviour->object).velocity;

		float distance = getLength(targetPosition - params.posComp->position);
		float updateDuration = distance / params.velComp->maxSpeed;

		params.targetPos = targetPosition + (targetVelocity * updateDuration * params.deltaTime);
	}
}

sf::Vector2f FollowSystem::Pursuit(ManageParams& params)
{
	PredictPostion(params);
	return Seek(params);
}

sf::Vector2f FollowSystem::Evade(ManageParams& params)
{
	PredictPostion(params);
	return Flee(params);
}

template <typename Compare>
sf::Vector2f FollowSystem::SeekOrFlee(ManageParams& params, Compare comp, bool inverse /*= false*/)
{
	sf::Vector2f targetPos = params.targetPos;
	auto desiredVelocity = targetPos - params.posComp->position;
	float distance = getLength(desiredVelocity);
	float radius = params.currentBehavior->slowingRadius;
	float max_speed = params.velComp->maxSpeed;

	params.info.distanceToTarget = distance;

	if (comp(distance, radius)) {
		float modifier = inverse ? (radius / distance) : (distance / radius);
		desiredVelocity = normalize(desiredVelocity) * modifier;
	}
	else {
		desiredVelocity = normalize(desiredVelocity) * max_speed;
	}

	if (inverse) {
		desiredVelocity *= -1;
	}

	auto steering = desiredVelocity - params.velComp->velocity;
	return steering;
}

sf::Vector2f FollowSystem::Seek(ManageParams& params)
{
	return SeekOrFlee(params, std::less<float>());
}

sf::Vector2f FollowSystem::Flee(ManageParams& params)
{
	return SeekOrFlee(params, std::greater<float>(), true);
}
