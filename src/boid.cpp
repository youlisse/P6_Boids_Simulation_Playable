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
void boids::setMaxForce(float value)
{
    maxForce = value;
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
void boids::refreshPos()
{
    position += velocity / 40.f;
}
