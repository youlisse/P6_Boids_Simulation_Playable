#include "enemyBoid.hpp"
#include "boid.hpp"
#include "flock.hpp"

void enemyBoid::setR(float value) //
{
    _rAvoid = value;
}
void enemyBoid::setRCohesion(float value) //
{
    _rCohesion = value;
}
void enemyBoid::setRAlign(float value) //
{
    _rAlign = value;
}
void enemyBoid::setMaxForce(float value) //
{
    _maxForce = value;
}
float enemyBoid::getR() const //
{
    return _rAvoid;
}
float enemyBoid::getRCohesion() const //
{
    return _rCohesion;
}
float enemyBoid::getRAlign() const //
{
    return _rAlign;
}
glm::vec2 enemyBoid::calculateSeparation(const std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context)
{
    glm::vec2 separation = {0.0, 0.0};
    int       count      = 0;
    for (const auto& boidPtr : boidsList)
    {
        const boid& currentBoid = *boidPtr;
        if (&currentBoid != this && currentBoid.whoAmI())
        {
            float distance = distanceTo(boidPtr, context);
            if (distance < _rAvoid && distance > 0.0f)
            {
                glm::vec2 diff = _position - glm::vec2(currentBoid.getX(), currentBoid.getY());
                separation += glm::normalize(diff);
                count += 1;
            }
        }
    }
    if (count > 0)
    {
        separation /= static_cast<float>(count);
    }
    return separation;
}

glm::vec2 enemyBoid::calculateAlignment(const std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context)
{
    glm::vec2 alignment = {0.0, 0.0};
    int       count     = 0;
    for (const auto& boidPtr : boidsList)
    {
        const boid& currentBoid = *boidPtr;
        if (&currentBoid != this && !currentBoid.whoAmI())
        {
            float distance = distanceTo(boidPtr, context);
            if (distance < _rAlign && distance > 0.0f)
            {
                alignment += glm::vec2(currentBoid.dirX(), currentBoid.dirY());
                count += 1;
            }
        }
    }
    if (count > 0)
    {
        alignment /= static_cast<float>(count);
        alignment = glm::normalize(alignment);
    }
    return alignment;
}

glm::vec2 enemyBoid::calculateCohesion(const std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context)
{
    glm::vec2 cohesion(0.0f);
    int       count = 0;
    for (const auto& boidPtr : boidsList)
    {
        const boid& currentBoid = *boidPtr;
        if (&currentBoid != this && !boidPtr->whoAmI())
        {
            float distance = distanceTo(boidPtr, context);
            if (distance < _rCohesion && distance > _rCohesion * 0.50f && distance > 0.0f)
            {
                cohesion += glm::vec2(boidPtr->getX(), boidPtr->getY());
                count += 1;
            }
        }
    }
    if (count > 0)
    {
        cohesion /= static_cast<float>(count);
        cohesion -= _position;
        cohesion = glm::normalize(cohesion);
    }
    return cohesion;
}

void enemyBoid::update(std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context, float percentSteering, paramSteering param)
{
    glm::vec2 avoid     = calculateSeparation(boidsList, context);
    glm::vec2 alignment = calculateAlignment(boidsList, context);
    glm::vec2 cohesion  = calculateCohesion(boidsList, context);
    // std::cout << cohesion[0] << " " << alignment[0] << " " << avoid[0] << " " << std::endl;

    glm::vec2 desiredDirection = avoid * param._Avoid + alignment * param._Align + cohesion * param._Cohesion;

    if (desiredDirection != glm::vec2(0.f))
        desiredDirection = glm::normalize(desiredDirection);

    auto steering = glm::vec2(0.f);
    if (glm::abs((desiredDirection).x - _direction.x) > _maxForce || glm::abs((desiredDirection).y - _direction.y) > _maxForce)
    {
        steering = glm::vec2(desiredDirection.x * _maxForce, desiredDirection.y * _maxForce);
    }
    else
    {
        steering = (desiredDirection);
    }

    _velocity += steering;

    _direction += _velocity * percentSteering;

    _direction = glm::normalize(_direction);

    _velocity *= 0;
}
