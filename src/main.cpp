#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

class boids {
private:
    glm::vec2 position;
    glm::vec2 acceleration; // acceleration
    glm::vec2 velocity;
    float     r;
    float     r_cohesion;
    float     r_align;
    float     maxSpeed{};
    float     maxForce{};

public:
    float getX() const { return position.x; }
    float getY() const { return position.y; }
    float dirX() const { return velocity.x; }
    float dirY() const { return velocity.y; }

    explicit boids(p6::Context& context)
        : position(p6::random::point(context.aspect_ratio())), acceleration(glm::vec2(.0f)), velocity(p6::random::direction()), r(0.2), r_cohesion(0.3), r_align(0.2), maxSpeed(2), maxForce(0.03)
    {
    }
    void applyForce(glm::vec2 force)
    {
        acceleration += force;
    }
    void refreshPos()
    {
        position += acceleration * velocity;
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

    float distance_to(boids other_boid)
    {
        float dx = other_boid.position[0] - position[0];
        float dy = other_boid.position[1] - position[1];
        return std::sqrt(dx * dx + dy * dy);
    }
    glm::vec2 calculateSeparation(const std::vector<boids>& boidsList)
    {
        glm::vec2 separation = {0.0, 0.0};
        int       count      = 0;
        for (boids boid : boidsList)
        {
            if (&boid != this)
            {
                float distance = distance_to(boid);
                if (distance < r)
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

    glm::vec2 calculateAlignment(const std::vector<boids>& boidsList)
    {
        glm::vec2 alignment(0.0f);
        int       count = 0;
        for (boids boid : boidsList)
        {
            if (&boid != this)
            {
                float distance = distance_to(boid);
                if (distance < r_align)
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

    glm::vec2 calculateCohesion(const std::vector<boids>& boidsList)
    {
        glm::vec2 cohesion(0.0f);
        int       count = 0;
        for (boids boid : boidsList)
        {
            if (&boid != this)
            {
                float distance = distance_to(boid);
                if (distance < r_cohesion)
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

    void update(const std::vector<boids>& boidsList)
    {
        // Calculate the separation, alignment, and cohesion vectors
        glm::vec2 separation = calculateSeparation(boidsList);
        glm::vec2 alignment  = calculateAlignment(boidsList);
        glm::vec2 cohesion   = calculateCohesion(boidsList);

        // Add the three vectors together to get the desired direction
        glm::vec2 desiredDirection = separation + alignment + cohesion;

        // Limit the desired direction to the maximum speed
        desiredDirection = glm::normalize(desiredDirection) * maxSpeed;

        // Calculate the steering force required to achieve the desired direction
        glm::vec2 steering = *new glm::vec2(0.f);
        if ((desiredDirection - velocity).x > maxForce || (desiredDirection - velocity).y > maxForce)
            steering = glm::vec2(maxForce);
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

        // Reset the acceleration to zero for the next update
        acceleration *= 0;
    }
};

class Flock {
private:
    std::vector<boids> boidsList;

public:
    void update()
    {
    }

    void flocking()
    {
        for (boids b : boidsList)
            b.update(boidsList);
    }
    void addBoids(boids boids)
    {
        boidsList.push_back(boids);
    }
};

std::vector<boids> initBoids(int nbElem, p6::Context& context)
{
    std::vector<boids> listedPosition;
    for (int i = 0; i < nbElem; i++)
    {
        boids b(context);
        listedPosition.push_back(b);
    }
    return listedPosition;
}

void refreshBoids(std::vector<boids>& listBoids, p6::Context& context)
{
    for (boids& i : listBoids)
    {
        i.refreshPos();
        i.checkOutOfBounce(context);
    }
}

void drawBoids(const std::vector<boids>& listedPosition, p6::Context& context)
{
    context.use_stroke = false;
    for (auto i : listedPosition)
        // context.square(p6::Center{i.getX(), i.getY()}, p6::Radius{0.1f});
        context.triangle(p6::Point2D((i.dirX()) * 0.05 + i.getX(), (i.dirY()) * 0.05 + i.getY()), p6::Point2D(i.getX() + (i.dirY()) * 0.02, i.getY() - (i.dirX()) * 0.02), p6::Point2D(i.getX() - (i.dirY()) * 0.02, i.getY() + (i.dirX()) * 0.02));
}
/* triangle pos(x,y) dir(x,y)  pos*/

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
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    // std::vector<glm::vec2> list = initPos(q, ctx);
    std::vector<boids> list = initBoids(20, ctx);

    ctx.maximize_window();
    // Declare your infinite update loop.
    ctx.update = [&]() {
        refreshBoids(list, ctx);
        ctx.background(p6::Color(0.2, 0.5, 0.05, 0.05));
        drawBoids(list, ctx);
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}