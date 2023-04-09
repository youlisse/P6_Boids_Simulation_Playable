#include "controllableBoid.hpp"

void controllableBoid::controlBoids(p6::Context& context)
{
    if (context.key_is_held(262)) // droite
    {
        velocity += glm::vec2(velocity.y / 7, -velocity.x / 7);
    }
    if (context.key_is_held(263)) // gauche
    {
        velocity += glm::vec2(-velocity.y / 7, velocity.x / 7);
    }
    checkOutOfBounce(context);
    velocity = glm::normalize(velocity);
    refreshPos();
}
