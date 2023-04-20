#include "boid.hpp"
#include "glm/fwd.hpp"

#ifndef OUR_BOID_HPP
#define OUR_BOID_HPP

class controllableBoid : public boids {
private:
    mutable float _health{};

public:
    ~controllableBoid() override = default;
    void  controlBoids(p6::Context& context);
    float getLife() const;
    void  addLife();
    explicit controllableBoid(p6::Context& context)
        : boids(context), _health(1.f)
    {
        this->_maxSpeed = .032f;
       this->_team = true ;
    };
};

#endif // OUR_BOID_HPP