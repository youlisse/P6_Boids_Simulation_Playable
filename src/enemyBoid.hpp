#ifndef ENEMY_BOID_HPP
#define ENEMY_BOID_HPP

#include "boid.hpp"
#include "controllableBoid.hpp"
#include "glm/fwd.hpp"

class enemyBoid : public boid {
private:
    float     _rAvoid{};
    float     _rCohesion{};
    float     _rAlign{};
    float     _maxForce{};
    glm::vec2 _velocity;

public:
    float getR() const override;
    float getRCohesion() const override;
    float getRAlign() const override;
    void  setR(float value) override;
    void  setRCohesion(float value) override;
    void  setRAlign(float value) override;
    void  setMaxForce(float value) override;

    ~enemyBoid() override = default;

    glm::vec2 calculateSeparation(const std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context);
    glm::vec2 calculateAlignment(const std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context);
    glm::vec2 calculateCohesion(const std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context);
    void      update(std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context, float percent, paramSteering param) override;
    explicit enemyBoid(p6::Context& context)
        : boid(context), _rAvoid(.045f), _rCohesion(.1f), _rAlign(.12f), _maxForce(0.9), _velocity(glm::vec2(.0f)) {}
    explicit enemyBoid(p6::Context& context, glm::vec2 pos)
        : boid(context), _rAvoid(.045f), _rCohesion(.1f), _rAlign(.12f), _maxForce(0.9), _velocity(glm::vec2(.0f))
    {
        _position = pos;
    }
};

#endif // ENEMY_BOID_HPP
