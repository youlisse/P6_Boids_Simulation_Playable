#ifndef ENEMY_BOID_HPP
#define ENEMY_BOID_HPP

#include "boid.hpp"
#include "controllableBoid.hpp"
#include "glm/fwd.hpp"

struct paramSteering {
    float _Avoid    = 0.3f;
    float _Cohesion = 0.4f;
    float _Align    = 0.5f;
};

class enemyBoid : public boids {
public:
    ~enemyBoid() override = default;

    glm::vec2 calculateSeparation(const std::vector<boids>& boidsList, p6::Context& context);
    glm::vec2 calculateAlignment(const std::vector<boids>& boidsList, p6::Context& context);
    glm::vec2 calculateCohesion(const std::vector<boids>& boidsList, p6::Context& context);
    void      update(const std::vector<boids>& boidsList, p6::Context& context, float percent, paramSteering param);
    explicit enemyBoid(p6::Context& context)
        : boids(context) {}
};

#endif // ENEMY_BOID_HPP
