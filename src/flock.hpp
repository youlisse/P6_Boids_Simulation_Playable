#pragma once
#include "boid.hpp"

struct paramRadius {
    float rAvoid    = 0.5f;
    float rCohesion = 0.5f;
    float rAlign    = 0.5f;
};
class Flock {
private:
    std::vector<boids> boidsList;

public:
    std::vector<boids> getList();
    Flock()
        : boidsList(*new std::vector<boids>()){};
    void refreshBoids(p6::Context& context);
    void flocking(p6::Context& context);
    void flocking(p6::Context& context, boids b);
    void addBoids(boids boids);
    void initBoids(int nbElem, p6::Context& context);
    void refreshParam(paramRadius para);
};
