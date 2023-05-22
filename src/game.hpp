#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include "draw.hpp"
#include "flock.hpp"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "imgui.h"
#include "p6/p6.h"
#include "saveScore.hpp"
void play(p6::Context& ctx, Flock& f, controllableBoid& myBoid, bool& trail, float& alpha, bool& radiusShow, float& stering, float& maxForce, paramSteering& paraSteering, paramRadius& paraRadius, int nbStart);
#endif