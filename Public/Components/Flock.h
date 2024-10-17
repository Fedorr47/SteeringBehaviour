#pragma once

enum class FlockRole : int
{
	Leader,
	Follower,
	NONE
};

struct FlockActor
{
	FlockActor()
	{
		role = FlockRole::NONE;
	}
	FlockRole role;
};

struct FlockFollower;
struct FlockLeader;

struct FlockLeader : public FlockActor
{
	FlockLeader() :
		FlockActor()
	{
		role = FlockRole::Leader;
	}
	std::vector<std::shared_ptr<FlockFollower>> followers;
};

struct FlockFollower : public FlockActor
{
	FlockFollower() :
		FlockActor()
	{
		role = FlockRole::Follower;
	}
	std::shared_ptr<FlockLeader> leader;
};