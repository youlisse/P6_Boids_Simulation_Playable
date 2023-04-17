#pragma once
#include <cstdlib>
#include <iostream>
#include <random>
#include <type_traits>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class boids {
protected:
    glm::vec2 _position;
    glm::vec2 _velocity;
    glm::vec2 _direction;
    float     _rAvoid{};
    float     _rCohesion{};
    float     _rAlign{};
    float     _maxSpeed{};
    float     _maxForce{};

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
        : _position(p6::random::point(context.aspect_ratio())), _velocity(glm::vec2(.0f)), _direction(p6::random::direction()), _rAvoid(.045f), _rCohesion(.1f), _rAlign(.12f), _maxSpeed(p6::random::number(0.013f, 0.028f)), _maxForce(0.9)
    {}

    boids(const boids&)            = default;
    boids& operator=(const boids&) = default;

    float distance_to(boids other_boid, p6::Context& context);
    void  refreshPos();
    void  checkOutOfBounce(p6::Context& context);
};
