struct WanderRanges
{
    float innerRange{ 0.0f };
    float outerRange{ 0.0f };
};

struct MovementBehaviour
{
    MovementBehaviour(
        entt::entity object,
        float slowingRadius) :
        object(object),
        slowingRadius(slowingRadius)
    {}
    entt::entity object;
    float slowingRadius{ 0 };
};

struct WanderBehavior : public MovementBehaviour
{
    WanderBehavior(
        entt::entity object,
        float slowingRadius,
        WanderRanges ranges,
        float timeWaiting,
        float circleDistance,
        float angleChange
    ) :
        MovementBehaviour(object, slowingRadius),
        ranges(ranges),
        timeWaiting(timeWaiting),
        circleDistance(circleDistance),
        angleChange(angleChange)
    {}
    WanderRanges ranges;
    float timeWaiting{ 0.0f };
    float nextDecisionTime{ 0.0f };
    float circleDistance{ 0.0f };
    float angleChange{ 0.0f };
    float wanderAngle{ 0.0f };
};