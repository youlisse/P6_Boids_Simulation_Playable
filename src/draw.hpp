#include "boid.hpp"
#include "controllableBoid.hpp"
#include "enemyBoid.hpp"
#include "flock.hpp"

void drawBoids(const std::vector<enemyBoid>& listedPosition, p6::Context& context);
void drawBoid(const controllableBoid& boid, p6::Context& context);
void drawRadius(const std::vector<enemyBoid>& listedPosition, p6::Context& context);
void drawRadius(const controllableBoid& boid, p6::Context& context, bool radiusShow);
void drawLife(float value, p6::Context& context);
void drawBackground(p6::Context& context, bool trail, float alpha);
void printScore(p6::Context& context, Flock& f);
void explosion(p6::Context& context, p6::Center pos);
