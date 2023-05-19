
#ifndef FLOCK_HPP
#define FLOCK_HPP
#pragma once
#include "boid.hpp"
#include "controllableBoid.hpp"
#include "enemyBoid.hpp"

struct paramRadius {
    float _rAvoid    = 0.3f;
    float _rCohesion = 0.4f;
    float _rAlign    = 0.5f;
};

class Flock {
private:
    // std::vector<enemyBoid> _enemyBoidsList;
    std::vector<std::unique_ptr<boid>> _boidsList;
    int                                _score;

public:
    std::vector<std::unique_ptr<boid>>& getList();
    Flock()
        : _score(0){};
    std::unique_ptr<boid>& returnMe();
    void                   refreshBoids(p6::Context& context);
    void                   flocking(p6::Context& context, float percent, paramSteering para);
    void                   addBoids(enemyBoid& boids);
    void                   initBoids(int nbElem, p6::Context& context, const controllableBoid& me);
    void                   refreshParam(paramRadius para, float maxForce);
    void                   killBoid(controllableBoid& b);
    void                   checkCollision(p6::Context& context, std::unique_ptr<boid>& ourBoid, float radius);
    int                    getScore() const;
    void                   reset();
};
#endif