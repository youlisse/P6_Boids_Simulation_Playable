#include "draw.hpp"
#include "boid.hpp"
#include "enemyBoid.hpp"
#include "flock.hpp"
#include "glm/geometric.hpp"

std::u16string to_u16string(int const& i)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::little_endian>, char16_t> conv;
    return conv.from_bytes(std::to_string(i));
}

void drawBoid(const std::unique_ptr<boid>& boid, p6::Context& context)
{
    float length       = 0.03 / 2.f;
    float thickness    = 0.025 / 2.f;
    context.use_fill   = true;
    context.use_stroke = false;
    context.fill       = {1.f, 1.f, 1.f, 1.0f};
    context.triangle(p6::Point2D((boid->dirX()) * length + boid->getX(), (boid->dirY()) * length + boid->getY()), p6::Point2D((boid->getX() + (boid->dirY()) * thickness) - ((boid->dirX()) * length), (boid->getY() - (boid->dirX()) * thickness) - ((boid->dirY()) * length)), p6::Point2D((boid->getX() - (boid->dirY()) * thickness) - ((boid->dirX()) * length), (boid->getY() + (boid->dirX()) * thickness) - ((boid->dirY()) * length)));
}

void drawBoids(const std::vector<std::unique_ptr<boid>>& listedPosition, p6::Context& context)
{
    float length       = 0.03 / 2.f;
    float thickness    = 0.02 / 2.f;
    context.use_fill   = true;
    context.use_stroke = false;

    for (const auto& b : listedPosition)
    {
        if (!b->whoAmI())
        {
            context.fill = {0.2f + (b->dirX() + b->dirY()) / 4, 0.2f + (b->dirX() + b->dirY()) / 4, 0.2f + (b->dirX() + b->dirY()) / 4.f, 1.f};
            context.triangle(p6::Point2D((b->dirX()) * length + b->getX(), (b->dirY()) * length + b->getY()), p6::Point2D((b->getX() + (b->dirY()) * thickness) - ((b->dirX()) * length), (b->getY() - (b->dirX()) * thickness) - ((b->dirY()) * length)), p6::Point2D((b->getX() - (b->dirY()) * thickness) - ((b->dirX()) * length), (b->getY() + (b->dirX()) * thickness) - ((b->dirY()) * length)));
        }
        else
            drawBoid(b, context);
    }
}

void drawRadius(const std::vector<std::unique_ptr<boid>>& listedPosition, p6::Context& context)
{
    context.use_stroke = false;
    for (const auto& b : listedPosition)
    {
        context.use_stroke = true;

        context.use_fill = false;
        context.stroke   = {0.1f, 0.3f, 0.4f, 1.0f};
        context.circle(glm::vec2(b->getX(), b->getY()), b->getR());
        context.stroke = {0.6f, 0.2f, 0.9f, 1.0f};
        context.circle(glm::vec2(b->getX(), b->getY()), b->getRAlign());
        context.stroke = {0.9f, 0.7f, 0.1f, 1.0f};
        context.circle(glm::vec2(b->getX(), b->getY()), b->getRCohesion());
    }
}
void drawRadius(const std::unique_ptr<boid>& boid, p6::Context& context, bool radiusShow, paramRadius paraRadius)
{
    if (!radiusShow)
        return;
    context.use_stroke = false;
    context.use_stroke = true;
    context.use_fill   = false;
    context.stroke     = {0.1f, 0.3f, 0.4f, 1.0f};
    context.circle(glm::vec2(boid->getX(), boid->getY()), paraRadius._rAlign);
    context.stroke = {0.6f, 0.2f, 0.9f, 1.0f};
    context.circle(glm::vec2(boid->getX(), boid->getY()), paraRadius._rAvoid);
    context.stroke = {0.9f, 0.7f, 0.1f, 1.0f};
    context.circle(glm::vec2(boid->getX(), boid->getY()), paraRadius._rCohesion);
}
void drawLife(float value, p6::Context& context)
{
    context.fill       = {.0f, .5f, 1.f, 1.0f};
    context.use_fill   = true;
    context.use_stroke = false;
    context.rectangle(p6::TopLeftCorner(-context.aspect_ratio(), 1.f), glm::vec2(value * context.aspect_ratio() / 5, 0.02f), p6::Angle());
}

void drawBackground(p6::Context& context, bool trail, float alpha)
{
    context.fill = {.9f, .9f, .9f, alpha};
    if (!trail)
        context.rectangle(p6::Center(), glm::vec2(context.aspect_ratio()), p6::Angle());
    else
        context.background(p6::Color(.9f, .9f, .9f, alpha));
}

void printScore(p6::Context& context, Flock& f)
{
    const std::u16string text = to_u16string(f.getScore());
    context.text(text, p6::Center(context.aspect_ratio() - context.aspect_ratio() / 33, 1.f - 0.07), p6::Angle());
}

void explosion(p6::Context& context, p6::Center pos)
{
    context.fill = {1.f, 1.f, 1.f, 1.0f};
    context.circle(p6::Center(pos), 0.1);
}
