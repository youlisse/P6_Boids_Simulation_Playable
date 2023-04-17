#include "boid.hpp"
#include "controllableBoid.hpp"
#include "enemyBoid.hpp"

void drawBoids(const std::vector<enemyBoid>& listedPosition, p6::Context& context);
void drawBoids(const controllableBoid& boid, p6::Context& context);
void drawRadius(const std::vector<enemyBoid>& listedPosition, p6::Context& context);
void drawRadius(const controllableBoid& boid, p6::Context& context);
void drawLife(float value, p6::Context& context);