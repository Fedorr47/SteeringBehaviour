#include "Systems/FollowSystem.h"

#include "Utils/Utils.h"
#include "Components/Components.h"

#include "ThirdParty/imgui/imgui-SFML.h"
#include "ThirdParty/imgui/imgui.h"

void FollowSystem::update(float deltaTime)
{
	auto view = registry.view<PositionComponent, VelocityComponent, ChasingComponent>();
	for (auto entity : view) 
	{
		auto& position = view.get<PositionComponent>(entity);
		ChasingComponent& chaising = view.get<ChasingComponent>(entity);
		VelocityComponent& velocity = view.get<VelocityComponent>(entity);

		ManageFollowParams params(
			static_cast<int>(entity),
			&registry,
			&velocity,
			&position,
			&chaising,
			deltaTime
		);
		ManageFollow(params);
	};
}

void FollowSystem::init()
{
	auto view = registry.view<VelocityComponent, ChasingComponent>();
	for (auto entity : view)
	{
		VelocityComponent& velocity = view.get<VelocityComponent>(entity);
		velocity.ruledBySteering = true;
	};
}

void FollowSystem::ManageFollow(ManageFollowParams& params)
{
	std::vector<sf::Vector2f> steerings;
	sf::Vector2f finalSteering(0.0f, 0.0f);
	float totalWeight = 0.0f;

	for (auto behavior : params.chasComp->Behaviors)
	{
		params.currentBehavior = behavior.get();
		sf::Vector2f steering;
		switch (behavior->type)
		{
		case MoveBehaviourType::Seek:
			[[fallthrough]];
		case MoveBehaviourType::Path:
			params.targetPos = params.reg->get<PositionComponent>(behavior->object).position;
			steering = Seek(params);
			break;
		case MoveBehaviourType::Flee:
			params.targetPos = params.reg->get<PositionComponent>(behavior->object).position;
			steering = Flee(params);
			break;
		case MoveBehaviourType::Wander:
			steering = Wander(params);
			break;
		case MoveBehaviourType::Pursuit:
			steering = Pursuit(params);
			break;
		case MoveBehaviourType::Evade:
			steering = Evade(params);
			break;
		default:
			break;
		}

		steerings.push_back(steering);

		params.info.entityID = params.entityID;
		params.info.position = params.posComp->position;
		params.info.velocity = params.velComp->velocity;
		debugInfo->chasingEntities[params.info.entityID] = params.info;
	}

	for (const auto& steering : steerings) {
		finalSteering += steering;
		totalWeight += 1.0f;
	}

	if (totalWeight > 0.0f) {
		finalSteering /= totalWeight;
	}

	params.velComp->steering += finalSteering;
}

sf::Vector2f FollowSystem::Wander(ManageFollowParams& params)
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

void FollowSystem::PredictPostion(ManageFollowParams& params)
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

sf::Vector2f FollowSystem::Pursuit(ManageFollowParams& params)
{
	PredictPostion(params);
	return Seek(params);
}

sf::Vector2f FollowSystem::Evade(ManageFollowParams& params)
{
	PredictPostion(params);
	return Flee(params);
}

template <typename Compare>
sf::Vector2f FollowSystem::SeekOrFlee(ManageFollowParams& params, Compare comp, bool inverse /*= false*/)
{
	float radius = params.currentBehavior->slowingRadius;
	float fullStopRadius = params.currentBehavior->stopRadius;
	float max_speed = params.velComp->maxSpeed;

	auto desiredVelocity = params.targetPos - params.posComp->position;
	float distance = getLength(desiredVelocity);
	
	params.info.distanceToTarget = distance;

	if (comp(distance, fullStopRadius))
	{
		params.velComp->velocity -= params.velComp->velocity;
		return sf::Vector2f(0.0f, 0.0f);
	}
	else if (comp(distance, radius)) 
	{
		float modifier = inverse ? (radius / distance) : (distance / radius);
		desiredVelocity = normalize(desiredVelocity) * modifier;
	}	
	else
	{
		desiredVelocity = normalize(desiredVelocity) * max_speed;
	}

	if (inverse) {
		desiredVelocity *= -1;
	}

	return desiredVelocity - params.velComp->velocity;
}

sf::Vector2f FollowSystem::Seek(ManageFollowParams& params)
{
	return SeekOrFlee(params, std::less<float>());
}

sf::Vector2f FollowSystem::Flee(ManageFollowParams& params)
{
	return SeekOrFlee(params, std::greater<float>(), true);
}
