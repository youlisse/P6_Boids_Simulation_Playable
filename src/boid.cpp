#include "boid.hpp"

float boids::getX() const
{
    return position.x;
}
float boids::getY() const
{
    return position.y;
}
float boids::dirX() const
{
    return velocity.x;
}
float boids::dirY() const
{
    return velocity.y;
}
float boids::getR() const
{
    return r;
}
float boids::getRCohesion() const
{
    return r_cohesion;
}
float boids::getRAlign() const
{
    return r_align;
}
void boids::setR(float value)
{
    r = value;
}
void boids::setRCohesion(float value)
{
    r_cohesion = value;
}
void boids::setRAlign(float value)
{
    r_align = value;
}

void boids::refreshPos()
{
    position += velocity * maxSpeed;
}

void boids::checkOutOfBounce(p6::Context& context)
{
    if (position.x > context.aspect_ratio())
        position.x = -context.aspect_ratio();
    if (position.x < -context.aspect_ratio())
        position.x = context.aspect_ratio();
    if (position.y > 1)
        position.y = -1;
    if (position.y < -1)
        position.y = 1;
}

void boids::controlBoids(p6::Context& context)
{
    if (context.key_is_held(262)) // droite
    {
        velocity += glm::vec2(velocity.y / 7, -velocity.x / 7);
    }
    if (context.key_is_held(263)) // gauche
    {
        velocity += glm::vec2(-velocity.y / 7, velocity.x / 7);
    }
    checkOutOfBounce(context);
    velocity = glm::normalize(velocity);
    refreshPos();
}

float boids::distance_to(boids other_boid, p6::Context& context)
{
    std::vector<float> tabDist;
    float              dx = other_boid.position[0] - position[0];
    float              dy = other_boid.position[1] - position[1];
    tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
    tabDist.push_back((std::sqrt(dx * dx + (dy + 2) * (dy + 2))));
    tabDist.push_back((std::sqrt(dx * dx + (dy - 2) * (dy - 2))));
    dx += 2 * context.aspect_ratio();

    tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
    tabDist.push_back((std::sqrt(dx * dx + (dy + 2) * (dy + 2))));
    tabDist.push_back((std::sqrt(dx * dx + (dy - 2) * (dy - 2))));
    dx -= 4 * context.aspect_ratio();

    tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
    tabDist.push_back((std::sqrt(dx * dx + (dy + 2) * (dy + 2))));
    tabDist.push_back((std::sqrt(dx * dx + (dy - 2) * (dy - 2))));

    return *std::min_element(tabDist.begin(), tabDist.end());
}

glm::vec2 boids::calculateSeparation(const std::vector<boids>& boidsList, p6::Context& context)
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
                glm::vec2 diff = position - boid.position;
                separation += glm::normalize(diff) / distance;
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

glm::vec2 boids::calculateAlignment(const std::vector<boids>& boidsList, p6::Context& context)
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
                alignment += boid.velocity;
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

glm::vec2 boids::calculateCohesion(const std::vector<boids>& boidsList, p6::Context& context)
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
                cohesion += boid.position;
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

void boids::update(const std::vector<boids>& boidsList, p6::Context& context)
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
    velocity += acceleration;
    // Limit the speed to the maximum speed
    /*if (velocity.x > maxSpeed)
        velocity = glm::vec2(maxSpeed, velocity.y);

    if (velocity.y > maxSpeed)
        velocity = glm::vec2(velocity.x, maxSpeed);*/

    // std::cout << velocity.x << velocity.y << std::endl;
    velocity = glm::normalize(velocity);

    acceleration *= 0;
}
