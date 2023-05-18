
#include "game.hpp"

void play(p6::Context& ctx, Flock& f, controllableBoid& myBoid, bool& trail, float& alpha, bool& radiusShow, float& stering, float& maxForce, paramSteering& paraSteering, paramRadius& paraRadius)
{
    f.initBoids(1, ctx, myBoid);
    ctx.update = [&]() {
        if (trail)
            ctx.framerate_capped_at(50.f);
        else
            ctx.framerate_capped_at(70.f);

        drawBackground(ctx, trail, alpha);
        f.returnMe()->controlBoids(ctx);
        f.flocking(ctx, stering, paraSteering);
        f.refreshBoids(ctx);
        f.refreshParam(paraRadius, maxForce);
        drawBoids(f.getList(), ctx);
        drawRadius(f.returnMe(), ctx, radiusShow, paraRadius);
        drawLife(f.returnMe()->refreshLife(), ctx);
        printScore(ctx, f);
        f.checkCollision(ctx, f.returnMe(), 0.05f);
    };
    // ctx.mouse_pressed = [&ctx](p6::MouseButton button) {
    //     std::cout << button.position.x << " " << button.position.y << "\n";
    //     // explosion(ctx, p6::Center(button.position.x, button.position.y));
    // };

    ctx.start();
}