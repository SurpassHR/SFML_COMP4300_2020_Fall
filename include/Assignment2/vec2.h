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
    void operator += (const Vec2 &rhs);
    void operator -= (const Vec2 &rhs);
    Vec2 operator * (const double rhs) const;
    Vec2 operator * (const Vec2 &rhs) const;
    void operator *= (const double rhs);
    void operator *= (const Vec2 &rhs);
    Vec2 operator / (const double rhs) const;
    void operator /= (const double rhs);
public:
    void normalize();
    Vec2 normalized();
    double length();
    double length2();
    sf::Vector2f vec2f();
    void print(const std::string &name);
    double dist(const Vec2 &rhs);
    double dist2(const Vec2 &rhs);
    double dot(const Vec2 &rhs);
    void rotate(const double angle);
};

#endif // VEC2_H