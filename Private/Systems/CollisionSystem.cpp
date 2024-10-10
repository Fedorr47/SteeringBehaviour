#include "Systems/CollisionSystem.h"

#include "Utils/Utils.h"
#include "Components/Components.h"


void CollisionSystem::update(float deltaTime)
{

}

// TODO: Move to some component (maybe to a new one)
constexpr float maxSeeAhead = 50.0f;

bool CollisionSystem::lineIntersectsCircle(sf::Vector2f& ahead, sf::Vector2f& ahead2, const sf::Vector2f& center, float radius)
{
    return distance(center, ahead) <= radius || distance(center, ahead2) <= radius;
}

sf::Vector2f CollisionSystem::CollosionAvoidance()
{
    /*
    auto position = params.posComp->position;
    auto velocity = params.velComp->velocity;
    sf::Vector2f avoidance;

    auto ahead = position + normalize(velocity) * maxSeeAhead;
    auto ahead2 = position + normalize(velocity) * maxSeeAhead * 0.5f;

    mostThreatening = findMostThreateningObstacle();
    var avoidance : Vector3D = new Vector3D(0, 0, 0);
    if (mostThreatening != null) {
        avoidance.x = ahead.x - mostThreatening.center.x;
        avoidance.y = ahead.y - mostThreatening.center.y;
        avoidance.normalize();
        avoidance.scaleBy(MAX_AVOID_FORCE);
    }
    else {
        avoidance.scaleBy(0); // nullify the avoidance force 
    }

    return avoidance;
    */
    return sf::Vector2f();
}