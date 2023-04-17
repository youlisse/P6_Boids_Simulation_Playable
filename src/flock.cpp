#include "flock.hpp"
#include "boid.hpp"
#include "controllableBoid.hpp"
#include "enemyBoid.hpp"

std::vector<enemyBoid> Flock::getList()
{
    return _enemyBoidsList;
}

void Flock::refreshBoids(p6::Context& context)
{
    for (enemyBoid& b : _enemyBoidsList)
    {
        b.checkOutOfBounce(context);

        b.refreshPos();
    }
}
void Flock::flocking(p6::Context& context, float percent)
{
    for (enemyBoid& boid : _enemyBoidsList)
    {
        boid.update(_boidsList, context, percent);
    }
}
void Flock::flocking(p6::Context& context, controllableBoid& b, float percent)
{
    std::vector<boids> boidsListPlusMe = _boidsList;
    boidsListPlusMe.push_back(b);
    for (enemyBoid& boid : _enemyBoidsList)
    {
        boid.update(boidsListPlusMe, context, percent);
    }
}

void Flock::addBoids(enemyBoid& boid)
{
    _enemyBoidsList.push_back(boid);
    _boidsList.push_back(boid);
}

void Flock::initBoids(int nbElem, p6::Context& context)
{
    for (int i = 0; i < nbElem; i++)
    {
        enemyBoid b(context);
        addBoids(b);
    }
}
void Flock::refreshParam(paramRadius para, float maxForce)
{
    for (enemyBoid& b : _enemyBoidsList)
    {
        b.setR(para._rAvoid);
        b.setRAlign(para._rAlign);
        b.setRCohesion(para._rCohesion);
        b.setMaxForce(maxForce);
    }
}
void Flock::killBoid(controllableBoid& b)
{
    b.lowerLife();
    if (!_enemyBoidsList.empty())
    {
        _enemyBoidsList.pop_back();
        _boidsList.pop_back();
    }
}