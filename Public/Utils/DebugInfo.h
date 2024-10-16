#pragma once
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <string>

struct FollowDebugInfo {
    int entityID{-1};
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f targetPos;
    float distanceToTarget{ 0.0f };
    float wanderAngle{ 0.0f };
};

class DebugInfo : public std::enable_shared_from_this<DebugInfo> {
    struct Private { explicit Private() = default; };
public:
    DebugInfo(Private) {}

    float fps;
    std::unordered_map<int, FollowDebugInfo> chasingEntities;

    static std::shared_ptr<DebugInfo> create()
    {
        return std::make_shared<DebugInfo>(Private());
    }

    std::shared_ptr<DebugInfo> getptr()
    {
        return shared_from_this();
    }
};