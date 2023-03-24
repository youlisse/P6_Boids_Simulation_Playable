#include "flock.hpp"

std::vector<boids> Flock::getList()
{
    return boidsList;
}

void Flock::refreshBoids(p6::Context& context)
{
    for (boids& b : boidsList)
    {
        b.refreshPos();
        b.checkOutOfBounce(context);
    }
}
void Flock::flocking(p6::Context& context)
{
    for (boids& b : boidsList)
    {
        b.update(boidsList, context);
    }
}
void Flock::flocking(p6::Context& context, boids b)
{
    std::vector<boids> boidsListPlusMe = boidsList;
    boidsListPlusMe.push_back(b);
    for (boids& b : boidsList)
    {
        b.update(boidsListPlusMe, context);
    }
}

void Flock::addBoids(boids boids)
{
    boidsList.push_back(boids);
}

void Flock::initBoids(int nbElem, p6::Context& context)
{
    for (int i = 0; i < nbElem; i++)
    {
        boids b(context);
        addBoids(b);
    }
}
void Flock::refreshParam(paramRadius para)
{
    for (boids& b : boidsList)
    {
        b.setR(para.rAvoid);
        b.setRAlign(para.rAlign);
        b.setRCohesion(para.rCohesion);
    }
}
