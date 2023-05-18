#include "controllableBoid.hpp"

void controllableBoid::controlBoids(p6::Context& context)
{
    if (context.key_is_held(262) || context.key_is_held(68)) // droite
    {
        _direction += glm::vec2(_direction.y / 7, -_direction.x / 7);
    }
    if (context.key_is_held(263) || context.key_is_held(81)) // gauche
    {
        _direction += glm::vec2(-_direction.y / 7, _direction.x / 7);
    }
    checkOutOfBounce(context);
    _direction = glm::normalize(_direction);
}
float controllableBoid::refreshLife() const
{
    this->_health -= 0.003f;
    return this->_health;
}
void controllableBoid::addLife()
{
    this->_health += 0.06f;
}
bool controllableBoid::imDeaD()
{
    return this->_health > 0;
}
