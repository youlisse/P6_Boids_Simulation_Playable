#pragma once
#include <cstdlib>
#include <iostream>
#include <random>
#include <type_traits>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class boids {
protected:
    glm::vec2 position;
    glm::vec2 acceleration;
    glm::vec2 velocity;
    float     r{};
    float     r_cohesion{};
    float     r_align{};
    float     maxSpeed{};
    float     maxForce{};

public:
    virtual ~boids() = default;
    float getX() const;
    float getY() const;
    float dirX() const;
    float dirY() const;
    float getR() const;
    float getRCohesion() const;
    float getRAlign() const;
    void  setR(float value);
    void  setRCohesion(float value);
    void  setRAlign(float value);
    void  setMaxForce(float value);

    explicit boids(p6::Context& context)
        : position(p6::random::point(context.aspect_ratio())), acceleration(glm::vec2(.0f)), velocity(p6::random::direction()), r(.045f), r_cohesion(.1f), r_align(.12f), maxSpeed(p6::random::number(0.005f, 0.02f)), maxForce(0.9)
    {}
    float distance_to(boids other_boid, p6::Context& context);
    void  refreshPos();
    void  checkOutOfBounce(p6::Context& context);
};