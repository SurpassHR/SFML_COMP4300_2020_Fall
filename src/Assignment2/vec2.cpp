#include "vec2.h"
#include <iostream>
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

void Vec2::operator += (const Vec2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
}

Vec2 Vec2::operator - (const Vec2 &rhs) const
{
    return { x - rhs.x, y - rhs.y };
}

void Vec2::operator -= (const Vec2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

Vec2 Vec2::operator * (const double rhs) const
{
    return { x * rhs, y + rhs };
}

Vec2 Vec2::operator * (const Vec2 &rhs) const
{
    return { x * rhs.x, y * rhs.y };
}

void Vec2::operator *= (const double rhs)
{
    x *= rhs;
    y *= rhs;
}

void Vec2::operator *= (const Vec2 &rhs)
{
    x *= rhs.x;
    y *= rhs.y;
}

Vec2 Vec2::operator / (const double rhs) const
{
    if (rhs == 0) {
        std::cerr << "divided by 0 err" << std::endl;
        return *this;
    }
    return { x / rhs, y / rhs };
}

void Vec2::operator /= (const double rhs)
{
    if (rhs == 0) {
        std::cerr << "divided by 0 err" << std::endl;
        return;
    }
    x /= rhs;
    y /= rhs;
}

void Vec2::normalize()
{
    if (length() == 0) {
        x = y = 0;
        return;
    }
    x /= length();
    y /= length();
}

double Vec2::length()
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}
sf::Vector2f Vec2::vec2f()
{
    return sf::Vector2f(x, y);
}

void Vec2::print(const std::string &name)
{
    std::cout << name << "[" << x << ", " << y << "]" << std::endl;
}

double Vec2::dist(const Vec2 &rhs)
{
    return std::sqrt(std::pow(rhs.x - x, 2) + std::pow(rhs.y - y, 2));
}


double Vec2::dist2(const Vec2 &rhs)
{
    return std::pow(rhs.x - x, 2) + std::pow(rhs.y - y, 2);
}