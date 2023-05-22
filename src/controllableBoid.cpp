#include "controllableBoid.hpp"

void controllableBoid::controlBoids(p6::Context& context)
{
    if (context.key_is_held(262) || context.key_is_held(68)) // droite
    {
        _direction += glm::vec2(_direction.y / 7, -_direction.x / 7);
    }
    if (context.key_is_held(263) || context.key_is_held(65)) // gauche
    {
        _direction += glm::vec2(-_direction.y / 7, _direction.x / 7);
    }
    checkOutOfBounce(context);
    _direction = glm::normalize(_direction);
}

float controllableBoid::life() const
{
    return this->_health;
}
void controllableBoid::refreshLife()
{
    this->_health -= 0.003f;
}
void controllableBoid::addLife()
{
    this->_health += 0.06f;
}
bool controllableBoid::imDead()
{
    return this->life() < 0.f;
}
