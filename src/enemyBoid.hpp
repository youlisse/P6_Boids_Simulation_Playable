#ifndef ENEMY_BOID_HPP
#define ENEMY_BOID_HPP

#include "boid.hpp"
#include "controllableBoid.hpp"
#include "glm/fwd.hpp"

class enemyBoid : public boids {
public:
    ~enemyBoid() override = default;
    glm::vec2 calculateSeparation(const std::vector<boids>& boidsList, p6::Context& context);
    glm::vec2 calculateAlignment(const std::vector<boids>& boidsList, p6::Context& context);
    glm::vec2 calculateCohesion(const std::vector<boids>& boidsList, p6::Context& context);
    void      update(const std::vector<boids>& boidsList, p6::Context& context, float percent);

    explicit enemyBoid(p6::Context& context)
        : boids(context) {}
};

#endif // ENEMY_BOID_HPP
