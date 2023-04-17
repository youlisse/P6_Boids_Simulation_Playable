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
    std::vector<enemyBoid> _enemyBoidsList;
    std::vector<boids>     _boidsList;

public:
    std::vector<enemyBoid> getList();
    Flock()
        : _enemyBoidsList(*new std::vector<enemyBoid>()), _boidsList(*new std::vector<boids>()){};
    void refreshBoids(p6::Context& context);
    void flocking(p6::Context& context, float percent);
    void flocking(p6::Context& context, controllableBoid& b, float percent);
    void addBoids(enemyBoid& boids);
    void initBoids(int nbElem, p6::Context& context);
    void refreshParam(paramRadius para, float maxForce);
    void killBoid(controllableBoid& b);
};
