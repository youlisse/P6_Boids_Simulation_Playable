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
#include "doctest/doctest.h"
#include "draw.hpp"
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
    f.initBoids(30, ctx);
    auto myBoid = boids(ctx);
    ctx.maximize_window();
    paramRadius para;
    float       alpha = 0.5f;

    bool radius_show = false;
    ctx.imgui        = [&]() {
        ImGui::Begin("param");
        ImGui::SliderFloat("Alpha", &alpha, 0.f, 1.f);
        ImGui::SliderFloat("avoidRadius", &para.rAvoid, 0.f, 1.f);
        ImGui::SliderFloat("cohesionRadius", &para.rCohesion, 0.f, 1.f);
        ImGui::SliderFloat("alignRadius", &para.rAlign, 0.f, 1.f);

        if (ImGui::Button("Show Radius"))
            radius_show = !radius_show;
        ImGui::End();
    };
    ctx.update = [&]() {
        myBoid.controlBoids(ctx);
        f.flocking(ctx, myBoid);
        f.refreshBoids(ctx);
        f.refreshParam(para);
        myBoid.setR(para.rAvoid);
        myBoid.setRAlign(para.rAlign);
        myBoid.setRCohesion(para.rCohesion);
        ctx.fill = {0.f, 0.f, 0.f, alpha};
        ctx.rectangle(p6::Center(), glm::vec2(ctx.aspect_ratio()), p6::Angle());

        drawBoids(f.getList(), ctx);
        if (radius_show)
            drawRadius(myBoid, ctx);
        drawBoids(myBoid, ctx);
    };
    ctx.start();
}