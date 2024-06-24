#ifndef VEC2_H
#define VEC2_H

#include <SFML/System.hpp>

class Vec2 {
public:
    Vec2(double x, double y) : x(x), y(y) {}
    Vec2(sf::Vector2f vec2f) : x(vec2f.x), y(vec2f.y) {}
    virtual ~Vec2() = default;
public:
    double x;
    double y;
public:
    bool operator == (const Vec2 &rhs) const;
    bool operator != (const Vec2 &rhs) const;
    Vec2 operator + (const Vec2 &rhs) const;
    Vec2 operator - (const Vec2 &rhs) const;
    Vec2 operator * (const double rhs) const;
    Vec2 operator / (const double rhs) const;
public:
    void normalize();
    double length();
};

#endif // VEC2_H