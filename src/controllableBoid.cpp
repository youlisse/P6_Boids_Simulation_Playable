#include "controllableBoid.hpp"

void controllableBoid::controlBoids(p6::Context& context)
{
    if (context.key_is_held(262)) // droite
    {
        _direction += glm::vec2(_direction.y / 7, -_direction.x / 7);
    }
    if (context.key_is_held(263)) // gauche
    {
        _direction += glm::vec2(-_direction.y / 7, _direction.x / 7);
    }
    checkOutOfBounce(context);
    _direction = glm::normalize(_direction);
    refreshPos();
}
float controllableBoid::getLife() const
{
    // std::cout << this->_health << '\n';
    this->_health -= 0.003f;
    return this->_health;
}
void controllableBoid::lowerLife()
{
    this->_health += 0.06f;
}