
#ifndef OUR_BOID_HPP
#define OUR_BOID_HPP
#include "boid.hpp"
#include "glm/fwd.hpp"

class controllableBoid : public boid {
private:
    mutable float _health{};

public:
    ~controllableBoid() override = default;
    void  controlBoids(p6::Context& context) override;
    float refreshLife() const override;
    void  addLife() override;
    explicit controllableBoid(p6::Context& context)
        : boid(context), _health(1.f)
    {
        this->_maxSpeed = .032f;
        this->_team     = true;
    };
    bool imDeaD();
};

#endif // OUR_BOID_HPP