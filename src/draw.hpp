#include "boid.hpp"

void drawBoids(const std::vector<boids>& listedPosition, p6::Context& context);
void drawBoids(boids boid, p6::Context& context);
void drawRadius(const std::vector<boids>& listedPosition, p6::Context& context);
void drawRadius(const boids boid, p6::Context& context);