#pragma once
#include "MovementBehaviour.h"

enum class FlockRole : int
{
	Leader,
	Follower,
	NONE
};

struct FlockActor
{
	FlockActor(entt::entity inId) :
		id(inId)
	{
		role = FlockRole::NONE;
	}
	FlockRole role;
	entt::entity id;
};

struct FlockFollower;
struct FlockLeader;

struct FlockLeader : public FlockActor
{
	FlockLeader(entt::entity inId) :
		FlockActor(inId)
	{
		role = FlockRole::Leader;
	}
	std::vector<entt::entity> followers;
};

struct FlockFollower : public FlockActor
{
	FlockFollower(entt::entity inId, entt::entity leaderId) :
		FlockActor(inId),
		leader(leaderId)
	{
		role = FlockRole::Follower;
	}
	std::shared_ptr<MovementBehavior> actualBehavior;
	std::shared_ptr<PursuitBehavior> arriveBehavior;
	std::shared_ptr<EvadeBehavior> evadeBehavior;
	entt::entity leader;
};