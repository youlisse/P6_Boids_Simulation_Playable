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
            float distance = distance_to(boid, context);
            if (distance < r && distance > 0.0f)
            {
                glm::vec2 diff = position - glm::vec2(boid.getX(), boid.getY());
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
            float distance = distance_to(boid, context);
            if (distance < r_align && distance > 0.0f)
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
            float distance = distance_to(boid, context);
            if (distance < r_cohesion && distance > r_cohesion * 0.50f && distance > 0.0f)
            {
                cohesion += glm::vec2(boid.getX(), boid.getY());
                count += 1;
            }
        }
    }
    if (count > 0)
    {
        cohesion /= static_cast<float>(count);
        cohesion -= position;
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
    if (glm::abs((desiredDirection).x - velocity.x) > maxForce || glm::abs((desiredDirection).y - velocity.y) > maxForce)
    {
        steering = glm::vec2(desiredDirection.x * maxForce, desiredDirection.y * maxForce);
    }
    else
    {
        steering = (desiredDirection);
    }

    acceleration += steering;

    // Update the velocity and position based on the acceleration
    velocity += acceleration * percent;
    // Limit the speed to the maximum speed
    /*if (velocity.x > maxSpeed)
        velocity = glm::vec2(maxSpeed, velocity.y);

    if (velocity.y > maxSpeed)
        velocity = glm::vec2(velocity.x, maxSpeed);*/

    // std::cout << velocity.x << velocity.y << std::endl;
    velocity = glm::normalize(velocity);

    acceleration *= 0;
}
