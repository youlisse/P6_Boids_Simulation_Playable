
#include "game.hpp"

void randomizer(float& stering, float& maxForce, paramSteering& paraSteering, paramRadius& paraRadius, int& nbStart)
{
    stering                = p6::random::number(0.1f, 1.0f);
    maxForce               = p6::random::number(0.1f, 1.0f);
    nbStart                = static_cast<int>(p6::random::number(0, 30)) + 20;
    paraSteering._Align    = p6::random::number(0.f, 1.f);
    paraSteering._Avoid    = p6::random::number(0.f, 1.f);
    paraSteering._Cohesion = p6::random::number(0.f, 1.f);
    paraRadius._rAvoid     = p6::random::number(0.f, .9f);
    paraRadius._rAvoid     = p6::random::number(0.f, .5f);
    paraRadius._rCohesion  = p6::random::number(0.f, .7f);
}

void play(p6::Context& ctx, Flock& f, controllableBoid& myBoid, bool& trail, float& alpha, bool& radiusShow, float& stering, float& maxForce, paramSteering& paraSteering, paramRadius& paraRadius, int& nbStart)
{
    ctx.update = [&]() {
        if (f.returnMe()->imDead())
        {
            // stop le jeu et display le score board

            ctx.pause();
            printReset(ctx, f);
            addScore(f.getScore());
            displayScores(ctx);
            f.reset();
            // Restart en Randomisant les param
            ctx.mouse_pressed = [&ctx](p6::MouseButton button) {
                ctx.resume();
            };
            myBoid = controllableBoid(ctx);
            randomizer(stering, maxForce, paraSteering, paraRadius, nbStart);
            f.initBoids(nbStart, ctx, myBoid);
        }
        else
        {
            // Game loop
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
            drawLife(f.returnMe()->life(), ctx);
            f.returnMe()->refreshLife();
            printScore(ctx, f);
            f.checkCollision(ctx, f.returnMe(), 0.05f);
        }
    };

    ctx.start();
}