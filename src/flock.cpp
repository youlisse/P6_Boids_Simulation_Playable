#include "flock.hpp"
#include "boid.hpp"
#include "controllableBoid.hpp"
#include "enemyBoid.hpp"

std::vector<enemyBoid> Flock::getList()
{
    return enemyBoidsList;
}

void Flock::refreshBoids(p6::Context& context)
{
    for (enemyBoid& b : enemyBoidsList)
    {
        b.checkOutOfBounce(context);

        b.refreshPos();
    }
}
void Flock::flocking(p6::Context& context, float percent)
{
    for (enemyBoid& boid : enemyBoidsList)
    {
        boid.update(boidsList, context, percent);
    }
}
void Flock::flocking(p6::Context& context, controllableBoid& b, float percent)
{
    std::vector<boids> boidsListPlusMe = boidsList;
    boidsListPlusMe.push_back(b);
    for (enemyBoid& boid : enemyBoidsList)
    {
        boid.update(boidsListPlusMe, context, percent);
    }
}

void Flock::addBoids(enemyBoid& boid)
{
    enemyBoidsList.push_back(boid);
    boidsList.push_back(boid);
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
    for (enemyBoid& b : enemyBoidsList)
    {
        b.setR(para.rAvoid);
        b.setRAlign(para.rAlign);
        b.setRCohesion(para.rCohesion);
        b.setMaxForce(maxForce);
    }
}
