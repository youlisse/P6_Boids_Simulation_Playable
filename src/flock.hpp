#pragma once
#include "boid.hpp"
#include "controllableBoid.hpp"
#include "enemyBoid.hpp"

struct paramRadius {
    float rAvoid    = 0.3f;
    float rCohesion = 0.4f;
    float rAlign    = 0.5f;
};
class Flock {
private:
    std::vector<enemyBoid> enemyBoidsList;
    std::vector<boids>     boidsList;

public:
    std::vector<enemyBoid> getList();
    Flock()
        : enemyBoidsList(*new std::vector<enemyBoid>()), boidsList(*new std::vector<boids>()){};
    void refreshBoids(p6::Context& context);
    void flocking(p6::Context& context, float percent);
    void flocking(p6::Context& context, controllableBoid& b, float percent);
    void addBoids(enemyBoid& boids);
    void initBoids(int nbElem, p6::Context& context);
    void refreshParam(paramRadius para, float maxForce);
};
