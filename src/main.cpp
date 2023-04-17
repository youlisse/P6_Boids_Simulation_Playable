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
    {
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }
    auto  _ctx = p6::Context{{.title = "Boids seeker"}};
    Flock _f   = *new Flock();
    _f.initBoids(80, _ctx);
    auto _myBoid = controllableBoid(_ctx);
    _ctx.maximize_window();
    paramRadius para;
    float       _alpha    = 0.2f;
    float       _stering  = 0.2f;
    float       _maxForce = 0.2f;

    bool _radius_show = false;
    bool _trail       = false;

    _ctx.imgui = [&]() {
        ImGui::Begin("param");
        if (ImGui::Button("trail"))
            _trail = !_trail;
        ImGui::SliderFloat("Alpha", &_alpha, 0.f, .1f);
        ImGui::SliderFloat("avoidRadius", &para._rAvoid, 0.f, .5f);
        ImGui::SliderFloat("cohesionRadius", &para._rCohesion, 0.f, .7f);
        ImGui::SliderFloat("alignRadius", &para._rAlign, 0.f, .9f);
        ImGui::SliderFloat("steringCoef", &_stering, 0.f, 1.f);
        ImGui::SliderFloat("maxForce", &_maxForce, 0.f, 1.f);

        if (ImGui::Button("Show Radius"))
            _radius_show = !_radius_show;
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
        _myBoid.controlBoids(_ctx);
        _f.flocking(_ctx, _myBoid, _stering);
        _f.refreshBoids(_ctx);
        _f.refreshParam(para, _maxForce);
        _myBoid.setR(para._rAvoid);
        _myBoid.setRAlign(para._rAlign);
        _myBoid.setRCohesion(para._rCohesion);

        _ctx.fill = {.9f, .9f, .9f, _alpha};
        if (!_trail)
            _ctx.rectangle(p6::Center(), glm::vec2(_ctx.aspect_ratio()), p6::Angle());
        else
            _ctx.background(p6::Color(.9f, .9f, .9f, _alpha));
        drawBoids(_f.getList(), _ctx);
        if (_radius_show)
            drawRadius(_myBoid, _ctx);
        drawBoids(_myBoid, _ctx);

        drawLife(_myBoid.getLife(), _ctx);
    };
    _ctx.start();
}