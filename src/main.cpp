#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "imgui.h"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

class boids {
private:
    glm::vec2 position;
    glm::vec2 acceleration; // acceleration
    glm::vec2 velocity;
    float     r{};
    float     r_cohesion{};
    float     r_align{};
    float     maxSpeed{};
    float     maxForce{};

public:
    float getX() const { return position.x; }
    float getY() const { return position.y; }
    float dirX() const { return velocity.x; }
    float dirY() const { return velocity.y; }
    float getR() const { return r; }
    float getRCohesion() const { return r_cohesion; }
    float getRAlign() const { return r_align; }

    explicit boids(p6::Context& context)
        : position(p6::random::point(context.aspect_ratio())), acceleration(glm::vec2(.0f)), velocity(p6::random::direction()), r(.05f), r_cohesion(.1f), r_align(.2f), maxSpeed(0.02), maxForce(0.03)
    {
    }
    void refreshPos()
    {
        position += velocity * 0.01f;
    }

    void checkOutOfBounce(p6::Context& context)
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

    float distance_to(boids other_boid, p6::Context& context)
    {
        std::vector<float> tabDist;
        float              dx = other_boid.position[0] - position[0];
        float              dy = other_boid.position[1] - position[1];
        tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
        tabDist.push_back((std::sqrt(dx * dx + (dy + 1) * (dy + 1))));
        tabDist.push_back((std::sqrt(dx * dx + (dy - 1) * (dy - 1))));
        dx += context.aspect_ratio();

        tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
        tabDist.push_back((std::sqrt(dx * dx + (dy + 1) * (dy + 1))));
        tabDist.push_back((std::sqrt(dx * dx + (dy - 1) * (dy - 1))));
        dx -= 2 * context.aspect_ratio();

        tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
        tabDist.push_back((std::sqrt(dx * dx + (dy + 1) * (dy + 1))));
        tabDist.push_back((std::sqrt(dx * dx + (dy - 1) * (dy - 1))));

        return *std::min_element(tabDist.begin(), tabDist.end());
    }

    glm::vec2 calculateSeparation(const std::vector<boids>& boidsList, p6::Context& context)
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

    glm::vec2 calculateAlignment(const std::vector<boids>& boidsList, p6::Context& context)
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

    glm::vec2 calculateCohesion(const std::vector<boids>& boidsList, p6::Context& context)
    {
        glm::vec2 cohesion(0.0f);
        int       count = 0;
        for (boids boid : boidsList)
        {
            if (&boid != this)
            {
                float distance = distance_to(boid, context);
                if (distance < r_cohesion && distance > 0.0f)
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

    void update(const std::vector<boids>& boidsList, p6::Context& context)
    {
        // Calculate the separation, alignment, and cohesion vectors
        glm::vec2 separation = calculateSeparation(boidsList, context);
        glm::vec2 alignment  = calculateAlignment(boidsList, context);
        glm::vec2 cohesion   = calculateCohesion(boidsList, context);

        // Add the three vectors together to get the desired direction
        glm::vec2 desiredDirection = separation + alignment + cohesion;

        // Limit the desired direction to the maximum speed
        if (desiredDirection != glm::vec2(0.f))
            desiredDirection = glm::normalize(desiredDirection);

        // Calculate the steering force required to achieve the desired direction
        auto steering = glm::vec2(0.f);
        if ((desiredDirection - velocity).x > maxForce || (desiredDirection - velocity).y > maxForce)
        {
            if ((desiredDirection - velocity).x > maxForce)
            {
                steering = glm::vec2(maxForce, desiredDirection.y - velocity.y);
            }
            if ((desiredDirection - velocity).y > maxForce)
            {
                steering = glm::vec2(desiredDirection.x - velocity.x, maxForce);
            }
        }
        else
            steering = (desiredDirection - velocity);

        // Apply the steering force to the acceleration
        acceleration += steering;

        // Update the velocity and position based on the acceleration
        velocity += acceleration;
        // Limit the speed to the maximum speed
        if (velocity.x > maxSpeed)
            velocity = glm::vec2(maxSpeed, velocity.y);

        if (velocity.y > maxSpeed)
            velocity = glm::vec2(velocity.x, maxSpeed);
        // std::cout << velocity.x << velocity.y << std::endl;
        velocity = glm::normalize(velocity);

        // Reset the acceleration to zero for the next update
        acceleration *= 0;
    }
};

class Flock {
private:
    std::vector<boids> boidsList;

public:
    std::vector<boids> getList() { return boidsList; }
    Flock()
        : boidsList(*new std::vector<boids>())
    {
    }

    void refreshBoids(p6::Context& context)
    {
        for (boids& b : boidsList)
        {
            b.refreshPos();
            b.checkOutOfBounce(context);
        }
    }

    void update()
    {
    }

    void flocking(p6::Context& context)
    {
        for (boids& b : boidsList)
        {
            b.update(boidsList, context);
        }
    }

    void addBoids(boids boids)
    {
        boidsList.push_back(boids);
    }

    void initBoids(int nbElem, p6::Context& context)
    {
        for (int i = 0; i < nbElem; i++)
        {
            boids b(context);
            addBoids(b);
        }
    }
};

void drawBoids(const std::vector<boids>& listedPosition, p6::Context& context)
{
    context.use_fill = true;

    context.use_stroke = false;
    context.fill       = {0.05f, 0.9f, 0.4f, 0.8f};
    for (auto b : listedPosition)
        context.triangle(p6::Point2D((b.dirX()) * 0.05 + b.getX(), (b.dirY()) * 0.05 + b.getY()), p6::Point2D(b.getX() + (b.dirY()) * 0.02, b.getY() - (b.dirX()) * 0.02), p6::Point2D(b.getX() - (b.dirY()) * 0.02, b.getY() + (b.dirX()) * 0.02));
}

void drawRadius(const std::vector<boids>& listedPosition, p6::Context& context)
{
    context.use_stroke = false;
    for (auto b : listedPosition)
    {
        context.use_stroke = true;

        context.use_fill = false;
        context.stroke   = {0.1f, 0.3f, 0.4f, 0.2f};
        context.circle(glm::vec2(b.getX(), b.getY()), b.getR());
        context.stroke = {0.6f, 0.2f, 0.9f, 0.3f};
        context.circle(glm::vec2(b.getX(), b.getY()), b.getRAlign());
        context.stroke = {0.9f, 0.7f, 0.1f, 0.5f};
        context.circle(glm::vec2(b.getX(), b.getY()), b.getRCohesion());
    }
}

////////////

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    //  Actual app
    auto  ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    Flock f   = *new Flock();
    f.initBoids(30, ctx);

    ctx.maximize_window();
    // Declare your infinite update loop.
    ctx.update = [&]() {
        f.flocking(ctx);
        f.refreshBoids(ctx);
        ctx.background(p6::Color(0.2, 0.5, 0.05, 0.05));
        drawBoids(f.getList(), ctx);
        drawRadius(f.getList(), ctx);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}