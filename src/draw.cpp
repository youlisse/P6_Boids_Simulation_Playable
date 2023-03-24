#include "draw.hpp"

void drawBoids(const std::vector<boids>& listedPosition, p6::Context& context)
{
    float length       = 0.03;
    float thickness    = 0.02;
    context.use_fill   = true;
    context.use_stroke = false;
    context.fill       = {0.05f, 0.9f, 0.4f, 1.0f};
    for (auto b : listedPosition)
        context.triangle(p6::Point2D((b.dirX()) * length + b.getX(), (b.dirY()) * length + b.getY()), p6::Point2D((b.getX() + (b.dirY()) * thickness) - ((b.dirX()) * length), (b.getY() - (b.dirX()) * thickness) - ((b.dirY()) * length)), p6::Point2D((b.getX() - (b.dirY()) * thickness) - ((b.dirX()) * length), (b.getY() + (b.dirX()) * thickness) - ((b.dirY()) * length)));
}
void drawBoids(boids boid, p6::Context& context)
{
    float length       = 0.03;
    float thickness    = 0.025;
    context.use_fill   = true;
    context.use_stroke = false;
    context.fill       = {0.9f, 0.2f, 0.1f, 1.0f};
    context.triangle(p6::Point2D((boid.dirX()) * length + boid.getX(), (boid.dirY()) * length + boid.getY()), p6::Point2D((boid.getX() + (boid.dirY()) * thickness) - ((boid.dirX()) * length), (boid.getY() - (boid.dirX()) * thickness) - ((boid.dirY()) * length)), p6::Point2D((boid.getX() - (boid.dirY()) * thickness) - ((boid.dirX()) * length), (boid.getY() + (boid.dirX()) * thickness) - ((boid.dirY()) * length)));
}

void drawRadius(const std::vector<boids>& listedPosition, p6::Context& context)
{
    context.use_stroke = false;
    for (auto b : listedPosition)
    {
        context.use_stroke = true;

        context.use_fill = false;
        context.stroke   = {0.1f, 0.3f, 0.4f, 1.0f};
        context.circle(glm::vec2(b.getX(), b.getY()), b.getR());
        context.stroke = {0.6f, 0.2f, 0.9f, 1.0f};
        context.circle(glm::vec2(b.getX(), b.getY()), b.getRAlign());
        context.stroke = {0.9f, 0.7f, 0.1f, 1.0f};
        context.circle(glm::vec2(b.getX(), b.getY()), b.getRCohesion());
    }
}
void drawRadius(const boids boid, p6::Context& context)
{
    context.use_stroke = false;
    context.use_stroke = true;
    context.use_fill   = false;
    context.stroke     = {0.1f, 0.3f, 0.4f, 1.0f};
    context.circle(glm::vec2(boid.getX(), boid.getY()), boid.getR());
    context.stroke = {0.6f, 0.2f, 0.9f, 1.0f};
    context.circle(glm::vec2(boid.getX(), boid.getY()), boid.getRAlign());
    context.stroke = {0.9f, 0.7f, 0.1f, 1.0f};
    context.circle(glm::vec2(boid.getX(), boid.getY()), boid.getRCohesion());
}