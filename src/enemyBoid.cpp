#include "enemyBoid.hpp"
#include "boid.hpp"

glm::vec2 enemyBoid::calculateSeparation(const std::vector<boids>& boidsList, p6::Context& context)
{
    glm::vec2 separation = {0.0, 0.0};
    int       count      = 0;
    for (boids boid : boidsList)
    {
        if (&boid != this)
        {
            float distance = distanceTo(boid, context);
            if (distance < _rAvoid && distance > 0.0f)
            {
                glm::vec2 diff = _position - glm::vec2(boid.getX(), boid.getY());
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

glm::vec2 enemyBoid::calculateAlignment(const std::vector<boids>& boidsList, p6::Context& context)
{
    glm::vec2 alignment(0.0f);
    int       count = 0;
    for (boids boid : boidsList)
    {
        if (&boid != this)
        {
            float distance = distanceTo(boid, context);
            if (distance < _rAlign && distance > 0.0f)
            {
                alignment += glm::vec2(boid.dirX(), boid.dirY());
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

glm::vec2 enemyBoid::calculateCohesion(const std::vector<boids>& boidsList, p6::Context& context)
{
    glm::vec2 cohesion(0.0f);
    int       count = 0;
    for (boids boid : boidsList)
    {
        if (&boid != this)
        {
            float distance = distanceTo(boid, context);
            if (distance < _rCohesion && distance > _rCohesion * 0.50f && distance > 0.0f)
            {
                cohesion += glm::vec2(boid.getX(), boid.getY());
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

void enemyBoid::update(const std::vector<boids>& boidsList, p6::Context& context, float percent)
{
    glm::vec2 separation = calculateSeparation(boidsList, context);
    glm::vec2 alignment  = calculateAlignment(boidsList, context);
    glm::vec2 cohesion   = calculateCohesion(boidsList, context);

    glm::vec2 desiredDirection = separation + alignment + cohesion;

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

    _direction += _velocity * percent;

    _direction = glm::normalize(_direction);

    _velocity *= 0;
}
