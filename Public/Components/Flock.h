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
	std::vector<std::shared_ptr<FlockFollower>> followers;
};

struct FlockFollower : public FlockActor
{
	FlockFollower(
		entt::entity inId, 
		entt::entity inLeaderId,
		std::shared_ptr<FlockLeader> inLeaderPtr) :
		FlockActor(inId),
		leaderId(inLeaderId)
	{
		leaderPtr = inLeaderPtr;
		role = FlockRole::Follower;
	}
	std::weak_ptr<FlockLeader> leaderPtr;
	std::shared_ptr<MovementBehavior> actualBehavior;
	std::shared_ptr<PursuitBehavior> arriveBehavior;
	std::shared_ptr<EvadeBehavior> evadeBehavior;
	entt::entity leaderId;
};