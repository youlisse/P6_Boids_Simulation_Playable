#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
// #include "GLFW/glfw3.h"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "imgui.h"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "boid.hpp"
#include "controllableBoid.hpp"
#include "doctest/doctest.h"
#include "draw.hpp"
#include "enemyBoid.hpp"
#include "flock.hpp"

int main(int argc, char* argv[])
{
    {
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }
    auto  ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    Flock f   = *new Flock();
    f.initBoids(80, ctx);
    auto myBoid = controllableBoid(ctx);
    ctx.maximize_window();
    ctx.background(1.0f);
    paramRadius para;
    float       alpha    = 0.2f;
    float       stering  = 0.2f;
    float       maxForce = 0.2f;

    bool radius_show = false;
    bool trail       = false;

    ctx.imgui = [&]() {
        ImGui::Begin("param");
        if (ImGui::Button("trail"))
            trail = !trail;
        ImGui::SliderFloat("Alpha", &alpha, 0.f, .1f);
        ImGui::SliderFloat("avoidRadius", &para.rAvoid, 0.f, .5f);
        ImGui::SliderFloat("cohesionRadius", &para.rCohesion, 0.f, .7f);
        ImGui::SliderFloat("alignRadius", &para.rAlign, 0.f, .9f);
        ImGui::SliderFloat("steringCoef", &stering, 0.f, 1.f);
        ImGui::SliderFloat("maxForce", &maxForce, 0.f, 1.f);

        if (ImGui::Button("Show Radius"))
            radius_show = !radius_show;
        ImGui::End();
    };
    ctx.update = [&]() {
        myBoid.controlBoids(ctx);
        f.flocking(ctx, myBoid, stering);
        f.refreshBoids(ctx);
        f.refreshParam(para, maxForce);
        myBoid.setR(para.rAvoid);
        myBoid.setRAlign(para.rAlign);
        myBoid.setRCohesion(para.rCohesion);

        ctx.fill = {.9f, .9f, .9f, alpha};
        if (!trail)
            ctx.rectangle(p6::Center(), glm::vec2(ctx.aspect_ratio()), p6::Angle());
        else
            ctx.background(p6::Color(.9f, .9f, .9f, alpha));
        drawBoids(f.getList(), ctx);
        if (radius_show)
            drawRadius(myBoid, ctx);
        drawBoids(myBoid, ctx);
    };
    ctx.start();
}