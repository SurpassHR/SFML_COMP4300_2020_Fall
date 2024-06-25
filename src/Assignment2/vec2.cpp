#include "vec2.h"
#include <cmath>

bool Vec2::operator == (const Vec2 &rhs) const
{
    return (x == rhs.x) && (y == rhs.y);
}

bool Vec2::operator != (const Vec2 &rhs) const
{
    return (x != rhs.x) || (y != rhs.y);
}

Vec2 Vec2::operator + (const Vec2 &rhs) const
{
    return { x + rhs.x, y + rhs.y };
}

Vec2 Vec2::operator - (const Vec2 &rhs) const
{
    return { x - rhs.x, y - rhs.y };
}

Vec2 Vec2::operator * (const double rhs) const
{
    return { x * rhs, y + rhs };
}

Vec2 Vec2::operator / (const double rhs) const
{
    return { x / rhs, y / rhs };
}

void Vec2::normalize()
{
    x /= length();
    y /= length();
}

double Vec2::length()
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}