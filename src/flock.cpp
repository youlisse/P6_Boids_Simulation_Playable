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
void Flock::flocking(p6::Context& context)
{
    for (enemyBoid& boid : enemyBoidsList)
    {
        boid.update(boidsList, context);
    }
}
void Flock::flocking(p6::Context& context, controllableBoid& b)
{
    std::vector<boids> boidsListPlusMe = boidsList;
    for (enemyBoid& boid : enemyBoidsList)
    {
        boid.update(boidsListPlusMe, context);
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
void Flock::refreshParam(paramRadius para)
{
    for (enemyBoid& b : enemyBoidsList)
    {
        b.setR(para.rAvoid);
        b.setRAlign(para.rAlign);
        b.setRCohesion(para.rCohesion);
    }
}
