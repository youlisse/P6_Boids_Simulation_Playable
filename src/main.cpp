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
#include "game.hpp"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "imgui.h"
#include "p6/p6.h"

// #include "GLFW/glfw3.h"
int main(int argc, char* argv[])

{
    paramRadius   _paraRadius;
    paramSteering _paraSteering;
    float         _alpha      = 0.2f;
    float         _stering    = 0.2f;
    float         _maxForce   = 0.2f;
    bool          _radiusShow = false;
    bool          _trail      = false;
    int           _nbStart    = 40;
    {
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }
    // creation de fenetre
    auto _ctx = p6::Context{{.title = "Boids seeker"}};
    _ctx.maximize_window();
    Flock            _f      = Flock();
    controllableBoid _myBoid = controllableBoid(_ctx);
    _f.initBoids(_nbStart, _ctx, _myBoid);
    // parameter ImGUI
    _ctx.imgui = [&]() {
        ImGui::Begin("param");
        if (ImGui::Button("trail"))
            _trail = !_trail;
        if (ImGui::Button("Show Radius"))
            _radiusShow = !_radiusShow;
        ImGui::SliderFloat("Alpha", &_alpha, 0.f, .1f);
        ImGui::SliderFloat("avoidRadius", &_paraRadius._rAvoid, 0.f, .5f);
        ImGui::SliderFloat("cohesionRadius", &_paraRadius._rCohesion, 0.f, .7f);
        ImGui::SliderFloat("alignRadius", &_paraRadius._rAlign, 0.f, .9f);
        ImGui::SliderFloat("avoidWeight", &_paraSteering._Avoid, 0.f, 1.f);
        ImGui::SliderFloat("cohesionWeight", &_paraSteering._Cohesion, 0.f, 1.f);
        ImGui::SliderFloat("alignWeight", &_paraSteering._Align, 0.f, 1.f);
        ImGui::SliderFloat("steringCoef", &_stering, 0.f, 1.f);
        ImGui::SliderFloat("maxForce", &_maxForce, 0.f, 1.f);

        if (ImGui::Button("Give birth"))
        {
            enemyBoid newBoid = enemyBoid(_ctx);
            _f.addBoids(newBoid);
        }
        ImGui::End();
    };
    /// create la party et relance la party onMouseClick
    play(_ctx, _f, _myBoid, _trail, _alpha, _radiusShow, _stering, _maxForce, _paraSteering, _paraRadius, _nbStart);
}