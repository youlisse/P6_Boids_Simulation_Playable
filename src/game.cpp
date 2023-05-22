
#include "game.hpp"

void play(p6::Context& ctx, Flock& f, controllableBoid& myBoid, bool& trail, float& alpha, bool& radiusShow, float& stering, float& maxForce, paramSteering& paraSteering, paramRadius& paraRadius, int nbStart)
{
    ctx.update = [&]() {
        if (f.returnMe()->imDead())
        {
            ctx.pause();
            printReset(ctx, f);
            addScore(f.getScore());
            displayScores(ctx);
            f.reset();

            ctx.mouse_pressed = [&ctx](p6::MouseButton button) {
                ctx.resume();
            };
            myBoid = controllableBoid(ctx);

            f.initBoids(nbStart, ctx, myBoid);
        }
        else
        {
            if (trail)
                ctx.framerate_capped_at(50.f);
            else
                ctx.framerate_capped_at(70.f);

            drawBackground(ctx, trail, alpha);
            f.returnMe()->controlBoids(ctx);
            f.flocking(ctx, stering, paraSteering);
            f.refreshBoids(ctx, nbStart);
            f.refreshParam(paraRadius, maxForce);
            drawBoids(f.getList(), ctx);
            drawRadius(f.returnMe(), ctx, radiusShow, paraRadius);
            drawLife(f.returnMe()->life(), ctx);
            f.returnMe()->refreshLife();
            printScore(ctx, f);
            f.checkCollision(ctx, f.returnMe(), 0.05f);
        }
    };

    ctx.start();
}