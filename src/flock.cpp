#include "flock.hpp"
#include <ratio>
#include <string>
#include "boid.hpp"
#include "controllableBoid.hpp"
#include "draw.hpp"
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
void Flock::flocking(p6::Context& context, float percentSteering, paramSteering para)
{
    for (enemyBoid& boid : _enemyBoidsList)
    {
        boid.update(_boidsList, context, percentSteering, para);
    }
}
void Flock::flocking(p6::Context& context, controllableBoid& b, float percent, paramSteering para)
{
    std::vector<boids> boidsListPlusMe = _boidsList;
    boidsListPlusMe.push_back(b);
    for (enemyBoid& boid : _enemyBoidsList)
    {
        boid.update(boidsListPlusMe, context, percent, para);
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
void Flock::refreshParam(paramRadius para, float maxForce, controllableBoid& ourBoid)
{
    for (enemyBoid& b : _enemyBoidsList)
    {
        b.setR(para._rAvoid);
        b.setRAlign(para._rAlign);
        b.setRCohesion(para._rCohesion);
        b.setMaxForce(maxForce);
    }
    ourBoid.setR(para._rAvoid);
    ourBoid.setRAlign(para._rAlign);
    ourBoid.setRCohesion(para._rCohesion);
    ourBoid.setMaxForce(maxForce);
}
void Flock::killBoid(controllableBoid& b)
{
    b.addLife();
    if (!_enemyBoidsList.empty())
    {
        _enemyBoidsList.pop_back();
        _boidsList.pop_back();
    }
}

void Flock::checkCollision(p6::Context& context, controllableBoid& ourBoid, float radius)
{
    float distance = 0.f;
    int   id       = -5;
    for (enemyBoid& b : _enemyBoidsList)
    {
        distance = b.distanceTo(ourBoid, context);
        if (distance < radius)
        {
            // kill boid
            id = b.getId();
            for (int i = 0; i < static_cast<int>(_enemyBoidsList.size()); i++)
                if (_enemyBoidsList[i].checkId(id))
                {
                    explosion(context, p6::Center(_enemyBoidsList[i].getX(), _enemyBoidsList[i].getY()));
                    _enemyBoidsList.erase(_enemyBoidsList.begin() + i);
                    _boidsList.erase(_boidsList.begin() + i);
                }
            // refresh life
            ourBoid.addLife();
            _score++;
        }
    }
}

int Flock::getScore() const
{
    return _score;
}