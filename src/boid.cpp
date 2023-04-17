#include "boid.hpp"

bool boids::checkId(int id) const
{
    return this->_id == id;
}

int boids::getId() const
{
    return this->_id;
}
float boids::getX() const
{
    return _position.x;
}
float boids::getY() const
{
    return _position.y;
}
float boids::dirX() const
{
    return _direction.x;
}
float boids::dirY() const
{
    return _direction.y;
}
void boids::setR(float value)
{
    _rAvoid = value;
}
void boids::setRCohesion(float value)
{
    _rCohesion = value;
}
void boids::setRAlign(float value)
{
    _rAlign = value;
}
void boids::setMaxForce(float value)
{
    _maxForce = value;
}
float boids::getR() const
{
    return _rAvoid;
}
float boids::getRCohesion() const
{
    return _rCohesion;
}
float boids::getRAlign() const
{
    return _rAlign;
}

void boids::checkOutOfBounce(p6::Context& context)
{
    if (_position.x > context.aspect_ratio())
        _position.x = -context.aspect_ratio();
    if (_position.x < -context.aspect_ratio())
        _position.x = context.aspect_ratio();
    if (_position.y > 1)
        _position.y = -1;
    if (_position.y < -1)
        _position.y = 1;
}

float boids::distanceTo(boids other_boid, p6::Context& context)
{
    std::vector<float> tabDist;
    float              dx = other_boid._position[0] - _position[0];
    float              dy = other_boid._position[1] - _position[1];
    tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
    tabDist.push_back((std::sqrt(dx * dx + (dy + 2) * (dy + 2))));
    tabDist.push_back((std::sqrt(dx * dx + (dy - 2) * (dy - 2))));
    dx += 2 * context.aspect_ratio();

    tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
    tabDist.push_back((std::sqrt(dx * dx + (dy + 2) * (dy + 2))));
    tabDist.push_back((std::sqrt(dx * dx + (dy - 2) * (dy - 2))));
    dx -= 4 * context.aspect_ratio();

    tabDist.push_back((std::sqrt(dx * dx + dy * dy)));
    tabDist.push_back((std::sqrt(dx * dx + (dy + 2) * (dy + 2))));
    tabDist.push_back((std::sqrt(dx * dx + (dy - 2) * (dy - 2))));

    return *std::min_element(tabDist.begin(), tabDist.end());
}
void boids::refreshPos()
{
    _position += _direction * _maxSpeed;
}
