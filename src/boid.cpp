#include "boid.hpp"
void cout()
{
    std::cout << " i'm there\n";
}
bool boid::checkId(int id) const
{
    return this->_id == id;
}

int boid::getId() const
{
    return this->_id;
}
float boid::getX() const
{
    return _position.x;
}
float boid::getY() const
{
    return _position.y;
}
float boid::dirX() const
{
    return _direction.x;
}
float boid::dirY() const
{
    return _direction.y;
}
void boid::setR(float value) //
{
}
void boid::setRCohesion(float value) //
{
}
void boid::setRAlign(float value) //
{
}
void boid::setMaxForce(float value) //
{
}
float boid::getR() const //
{
    return 0;
}
float boid::getRCohesion() const //
{
    return 0;
}
float boid::getRAlign() const //
{
    return 0;
}

void boid::update(std::vector<std::unique_ptr<boid>>& boidsList, p6::Context& context, float percent, paramSteering param)
{
    // cout();
}
void boid::controlBoids(p6::Context& context)
{}
void boid::refreshLife()
{
}
float boid::life() const
{
    return 0.0;
}

void boid::addLife()
{
}
bool boid::imDead()
{
    return false;
}

float boid::distanceTo(const std::unique_ptr<boid>& other_boid, p6::Context& context)
{
    std::vector<float> tabDist;
    // float              dx = 0.f;
    // float              dy = 0.f;
    float dx = other_boid->getX() - this->getX();
    float dy = other_boid->getY() - this->getY();
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

void boid::checkOutOfBounce(p6::Context& context)
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

void boid::refreshPos()
{
    _position += _direction * _maxSpeed * 0.4f;
}

bool boid::whoAmI() const
{
    return _team;
}
