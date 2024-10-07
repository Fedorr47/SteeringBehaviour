#pragma once

enum class MoveBehaviourType : char
{
    Seek,
    Flee,
    Wander,
    Pursuit,
    Evade,
    NONE
};

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

struct SeekFleeBehavior : public MovementBehaviour
{
    SeekFleeBehavior(
        entt::entity object,
        float slowingRadius) :
        MovementBehaviour(object, slowingRadius)
    {}
};

struct PursuitEvadeBehavior : public SeekFleeBehavior
{
    PursuitEvadeBehavior(
        entt::entity object,
        float slowingRadius) :
        SeekFleeBehavior(object, slowingRadius)
    {}
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