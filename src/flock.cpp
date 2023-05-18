#include "flock.hpp"
#include <ratio>
#include <string>
#include <vector>
#include "boid.hpp"
#include "controllableBoid.hpp"
#include "draw.hpp"
#include "enemyBoid.hpp"

std::unique_ptr<boid>& Flock::returnMe()
{
    for (auto& b : _boidsList)
        if (b->whoAmI())
            return b;
}
std::vector<std::unique_ptr<boid>>& Flock::getList()
{
    return _boidsList;
}

void Flock::refreshBoids(p6::Context& context)
{
    for (auto& b : _boidsList)
    {
        b->checkOutOfBounce(context);
        b->refreshPos();
    }
}

void Flock::flocking(p6::Context& context, float percent, paramSteering para)
{
    for (auto& b : _boidsList)
    {
        b->update(_boidsList, context, percent, para);
    }
}

void Flock::addBoids(enemyBoid& b)
{
    _boidsList.push_back(std::make_unique<enemyBoid>(b));
}

void Flock::initBoids(int nbElem, p6::Context& context, const controllableBoid& me)
{
    for (int i = 0; i < nbElem; i++)
    {
        enemyBoid b(context);
        addBoids(b);
    }
    _boidsList.push_back(std::make_unique<controllableBoid>(me));
}
void Flock::refreshParam(paramRadius para, float maxForce)
{
    for (auto& b : _boidsList)
    {
        if (!b->whoAmI())
        {
            b->setR(para._rAvoid);
            b->setRAlign(para._rAlign);
            b->setRCohesion(para._rCohesion);
            b->setMaxForce(maxForce);
        }
    }
    // ourBoid.setR(para._rAvoid);
    // ourBoid.setRAlign(para._rAlign);
    // ourBoid.setRCohesion(para._rCohesion);
    // ourBoid.setMaxForce(maxForce);
}
void Flock::killBoid(controllableBoid& b)
{
    b.addLife();
    if (!_boidsList.empty())
    {
        _boidsList.pop_back();
    }
}

void Flock::checkCollision(p6::Context& context, std::unique_ptr<boid>& ourBoid, float radius)
{
    float                              distance = 0.f;
    std::vector<std::unique_ptr<boid>> erasable;
    for (auto it = _boidsList.begin(); it != _boidsList.end();)
    {
        auto& b = *it;
        if (!b->whoAmI())
        {
            distance = b->distanceTo(ourBoid, context);
            if (distance < radius)
            {
                // kill boid
                explosion(context, p6::Center(b->getX(), b->getY()));
                // refresh life
                ourBoid->addLife();
                _score++;
                // erasable.push_back(std::move(b));
                it = _boidsList.erase(it);
                // si je continue a tourné sur it j'ai une seg fault je pense c'est car je change la taille de boidlist donc n'a pas le meme boidlist.end
                it = _boidsList.end();
            }
            else
            {
                ++it;
            }
        }
        else
        {
            ++it;
        }
    }
}

int Flock::getScore() const
{
    return _score;
}