#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <SFML/Graphics.hpp>

class Vec2 {
public:
    Vec2(int x, int y) : m_x(x), m_y(y) {}
    virtual ~Vec2() {}
public:
    float X() const { return m_x; }
    float Y() const { return m_y; }
    float Len() const { return std::sqrt(m_x * m_x + m_y * m_y); }
    float HoriAngle() const { return std::atan2(m_y, m_x); }
    float VertAngle() const { return std::atan2(m_x, m_y); }
    sf::Vector2f Normalize() const { return { m_x / Len(), m_y / Len() }; }
public:
    sf::Vector2f operator + (const Vec2 &rhs) const
    {
        return { m_x + rhs.X(), m_y + rhs.Y() };
    }
    sf::Vector2f operator + (const sf::Vector2f &rhs) const
    {
        return { m_x + rhs.x, m_y + rhs.y};
    }
    sf::Vector2f operator - (const Vec2 &rhs) const
    {
        return { m_x - rhs.X(), m_y - rhs.Y() };
    }
    sf::Vector2f operator - (const sf::Vector2f &rhs) const
    {
        return { m_x - rhs.x, m_y - rhs.y };
    }
    bool operator = (const Vec2 &rhs) const 
    {
        return (m_x == rhs.X()) && (m_y == rhs.Y());
    }
    bool operator = (const sf::Vector2f &rhs) const 
    {
        return (m_x == rhs.x) && (m_y == rhs.y);
    }
private:
    float m_x{ 0 };
    float m_y{ 0 };
};

#endif