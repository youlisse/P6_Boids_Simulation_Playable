#include <cstdlib>
#include <iostream>
#include <random>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

class boids {
private:
    glm::vec2 position;
    glm::vec2 direction;
    float     velocity;
    void      refreshPos()
    {
    }
};

std::vector<glm::vec2> initPos(int nbElem, p6::Context& context)
{
    std::vector<glm::vec2> listedPosition;
    glm::vec2              pos{};
    for (int i = 0; i < nbElem; i++)
    {
        pos.x = ((random() % 100) * context.aspect_ratio() / 50.0) - context.aspect_ratio();
        pos.y = ((random() % 100) / 50.0) - 1;
        listedPosition.push_back(pos);
    }
    return listedPosition;
}

void checkOutOfBounce(glm::vec2& pos, p6::Context& context)
{
    if (pos.x > context.aspect_ratio())
        pos.x = -context.aspect_ratio();
    if (pos.x < -context.aspect_ratio())
        pos.x = context.aspect_ratio();
    if (pos.y > 1)
        pos.y = -1;
    if (pos.y < -1)
        pos.y = 1;
}

void updatePos(std::vector<glm::vec2>& listedPos, glm::vec2 direction, p6::Context& context)
{
    for (glm::vec2& i : listedPos)
    {
        i.x += direction.x;
        i.y += direction.y;
        checkOutOfBounce(i, context);
    }
    // std::cout << " ma pos " << listedPos[1].x << "" << listedPos[1].y << std::endl;
}

void drawSquares(const std::vector<glm::vec2> listedPosition, p6::Context& context)
{
    for (auto i : listedPosition)
        context.square(p6::Center{i.x, i.y}, p6::Radius{0.02f});
}

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned>(time(nullptr)));
    int q = 15;

    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }
    auto dir = glm::vec2(0.01);
    // Actual app
    auto                   ctx  = p6::Context{{.title = "Simple-p6-Setup"}};
    std::vector<glm::vec2> list = initPos(q, ctx);

    ctx.maximize_window();
    // Declare your infinite update loop.
    ctx.update = [&]() {
        // std::cout << ctx.mouse().x << " " << ctx.mouse().y << " " << ctx.aspect_ratio() << std::endl;
        // std::cout << list[1].x << " " << list[1].y << std::endl;
        updatePos(list, dir, ctx);
        ctx.background(p6::Color(0.2, 0.5, 0.4, 0.1));
        drawSquares(list, ctx);
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}