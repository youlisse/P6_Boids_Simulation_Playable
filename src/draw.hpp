#include "boid.hpp"
#include "controllableBoid.hpp"
#include "enemyBoid.hpp"
#include "flock.hpp"

void drawBoids(const std::vector<std::unique_ptr<boid>>& listedPosition, p6::Context& context);
void drawBoid(const std::unique_ptr<boid>& boid, p6::Context& context);
void drawRadius(const std::vector<std::unique_ptr<boid>>& listedPosition, p6::Context& context);
void drawRadius(const std::unique_ptr<boid>& boid, p6::Context& context, bool radiusShow, paramRadius _paraRadius);
void drawLife(float value, p6::Context& context);
void drawBackground(p6::Context& context, bool trail, float alpha);
void printScore(p6::Context& context, Flock& f);
void explosion(p6::Context& context, p6::Center pos);
void printReset(p6::Context& context, Flock& f);
