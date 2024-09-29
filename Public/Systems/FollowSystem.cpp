#include "FollowSystem.h"

void ManageFollow(VelocityComponent& velocity, ChaisingComponent& chaisingComp)
{
	switch (chaisingComp.type)
	{
	case MoveBehaviourType::Seek:
		chaisingComp.velocity_multiplier = 1;
		break;
	case MoveBehaviourType::Flee:
		chaisingComp.velocity_multiplier = -1;
		break;
	default:
		break;
	}
	velocity.velocity *= chaisingComp.velocity_multiplier;
}
