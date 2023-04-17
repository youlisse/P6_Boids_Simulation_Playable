#define DOCTEST_CONFIG_IMPLEMENT
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include "boid.hpp"
#include "controllableBoid.hpp"
#include "doctest/doctest.h"
#include "draw.hpp"
#include "enemyBoid.hpp"
#include "flock.hpp"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "imgui.h"
#include "p6/p6.h"
// #include "GLFW/glfw3.h"
int main(int argc, char* argv[])

{
    paramRadius para;
    float       _alpha      = 0.2f;
    float       _stering    = 0.2f;
    float       _maxForce   = 0.2f;
    bool        _radiusShow = false;
    bool        _trail      = false;
    {
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }
    auto _ctx = p6::Context{{.title = "Boids seeker"}};
    _ctx.maximize_window();

    Flock _f = *new Flock();
    _f.initBoids(10, _ctx);
    controllableBoid _myBoid = controllableBoid(_ctx);

    _ctx.imgui = [&]() {
        ImGui::Begin("param");
        if (ImGui::Button("trail"))
            _trail = !_trail;
        if (ImGui::Button("Show Radius"))
            _radiusShow = !_radiusShow;
        ImGui::SliderFloat("Alpha", &_alpha, 0.f, .1f);
        ImGui::SliderFloat("avoidRadius", &para._rAvoid, 0.f, .5f);
        ImGui::SliderFloat("cohesionRadius", &para._rCohesion, 0.f, .7f);
        ImGui::SliderFloat("alignRadius", &para._rAlign, 0.f, .9f);
        ImGui::SliderFloat("steringCoef", &_stering, 0.f, 1.f);
        ImGui::SliderFloat("maxForce", &_maxForce, 0.f, 1.f);
        if (ImGui::Button("Execute innocent boid"))
            _f.killBoid(_myBoid);
        if (ImGui::Button("Give birth"))
        {
            enemyBoid newBoid = enemyBoid(_ctx);
            _f.addBoids(newBoid);
        }
        ImGui::End();
    };
    _ctx.update = [&]() {
        drawBackground(_ctx, _trail, _alpha);
        _myBoid.controlBoids(_ctx);
        _f.flocking(_ctx, _myBoid, _stering);
        _f.refreshBoids(_ctx);
        _f.refreshParam(para, _maxForce, _myBoid);
        _f.checkCollision(_ctx, _myBoid, 0.1f);
        drawBoids(_f.getList(), _ctx);
        drawRadius(_myBoid, _ctx, _radiusShow);
        drawBoid(_myBoid, _ctx);
        drawLife(_myBoid.getLife(), _ctx);
    };
    _ctx.start();
}