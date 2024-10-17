#pragma once

enum class MoveBehaviourType : char
{
    Seek,
    Flee,
    Wander,
    Pursuit,
    Evade,
    Path,
    NONE
};

inline static const std::unordered_map<MoveBehaviourType, const std::string> MovementBehaviorNames{
    {MoveBehaviourType::Seek,"Seek"},
    {MoveBehaviourType::Flee,"Flee"},
    {MoveBehaviourType::Wander,"Wander"},
    {MoveBehaviourType::Pursuit,"Pursuit"},
    {MoveBehaviourType::Evade,"Evade"},
    {MoveBehaviourType::Path,"Path"}
};

struct WanderRanges
{
    float innerRange{ 0.0f };
    float outerRange{ 0.0f };
};

// TODO: Replace all of them to syb-systems
struct MovementBehavior
{
    MoveBehaviourType type = MoveBehaviourType::Seek;
    MovementBehavior(
        entt::entity object,
        float slowingRadius) :
        object(object),
        type(type),
        slowingRadius(slowingRadius)
    {
        type = MoveBehaviourType::NONE;
    }
    entt::entity object;
    float slowingRadius{ 0 };
};

struct SeekBehavior : public MovementBehavior
{
    SeekBehavior(
        entt::entity object,
        float slowingRadius) :
        MovementBehavior(object, slowingRadius)
    {
        type = MoveBehaviourType::Seek;
    }
};

struct FleeBehavior : public MovementBehavior
{
    FleeBehavior(
        entt::entity object,
        float slowingRadius) :
        MovementBehavior(object, slowingRadius)
    {
        type = MoveBehaviourType::Flee;
    }
};

struct PursuitBehavior : public SeekBehavior
{
    PursuitBehavior(
        entt::entity object,
        float slowingRadius) :
        SeekBehavior(object, slowingRadius)
    {
        type = MoveBehaviourType::Pursuit;
    }
};

struct EvadeBehavior : public FleeBehavior
{
    EvadeBehavior(
        entt::entity object,
        float slowingRadius) :
        FleeBehavior(object, slowingRadius)
    {
        type = MoveBehaviourType::Evade;
    }
};

struct WanderBehavior : public MovementBehavior
{
    WanderBehavior(
        float slowingRadius,
        WanderRanges ranges,
        float timeWaiting,
        float circleDistance,
        float angleChange
    ) :
        MovementBehavior(entt::null, slowingRadius),
        ranges(ranges),
        timeWaiting(timeWaiting),
        circleDistance(circleDistance),
        angleChange(angleChange)
    {
        type = MoveBehaviourType::Wander;
    }
    WanderRanges ranges;
    float timeWaiting{ 0.0f };
    float nextDecisionTime{ 0.0f };
    float circleDistance{ 0.0f };
    float angleChange{ 0.0f };
    float wanderAngle{ 0.0f };
};

struct PathBehavior : public SeekBehavior
{
    PathBehavior(
        entt::entity object,
        float slowingRadius) :
        SeekBehavior(object, slowingRadius)
    {
        type = MoveBehaviourType::Path;
    }
};

struct NodeOfPath
{
    entt::entity id{ entt::null };
    sf::Vector2f position;
};
