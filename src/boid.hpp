
#ifndef BOID_HPP
#define BOID_HPP
#pragma once
#include <cstdlib>
#include <iostream>
#include <random>
#include <type_traits>
#include "glm/fwd.hpp"
#include "p6/p6.h"

void cout();
struct paramSteering {
    float _Avoid    = 0.3f;
    float _Cohesion = 0.4f;
    float _Align    = 0.5f;
};

class boid {
private:
    inline static int _cpt = 0;
    int               _id;

protected:
    bool      _team;
    glm::vec2 _position;
    glm::vec2 _direction;
    float     _maxSpeed{};

public:
    bool whoAmI() const;
    virtual ~boid() = default;
    bool          checkId(int id) const;
    int           getId() const;
    float         getX() const;
    float         getY() const;
    float         dirX() const;
    float         dirY() const;
    virtual float getR() const;
    virtual float getRCohesion() const;
    virtual float getRAlign() const;
    virtual void  setR(float r);
    virtual void  setRAlign(float r);
    virtual void  setRCohesion(float r);
    virtual void  setMaxForce(float r);
    virtual void  update(std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context, float percent, paramSteering param);
    virtual void  controlBoids(p6::Context& context);
    virtual void  refreshLife();
    virtual void  addLife();
    virtual float life() const;
    virtual bool  imDead();

    explicit boid(p6::Context& context)
        : _id(_cpt++), _team(false), _position(p6::random::point(context.aspect_ratio())), _direction(p6::random::direction()), _maxSpeed(p6::random::number(0.013f, 0.028f)) {}

    boid(const boid&)            = default;
    boid& operator=(const boid&) = default;
    float distanceTo(const std::unique_ptr<boid>& other_boid, p6::Context& context);

    void refreshPos();
    void checkOutOfBounce(p6::Context& context);
};
#endif