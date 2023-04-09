#include "boid.hpp"
#include "glm/fwd.hpp"

#ifndef OUR_BOID_HPP
#define OUR_BOID_HPP

class controllableBoid : public boids {
public:
    ~controllableBoid() override = default;
    void controlBoids(p6::Context& context);
    explicit controllableBoid(p6::Context& context)
        : boids(context){};
};

#endif // OUR_BOID_HPP