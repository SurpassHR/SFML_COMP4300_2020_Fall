#include "shape.h"

Shape::Shape(float radius, float points, const sf::Color &fill, const sf::Color &outline, float thickness)
    : circle(radius, points)
{
    circle.setFillColor(fill);
    circle.setOutlineColor(outline);
    circle.setOutlineThickness(thickness);
    circle.setPosition(radius, radius);
    circle.setOrigin(radius, radius);
}

Shape::Shape(std::shared_ptr<Shape> s)
    : circle(s->circle.getRadius(), s->circle.getPointCount())
{
    circle.setFillColor(s->circle.getFillColor());
    circle.setOutlineColor(s->circle.getOutlineColor());
    circle.setOutlineThickness(s->circle.getOutlineThickness());
    circle.setPosition(s->circle.getPosition());
    circle.setOrigin(s->circle.getOrigin());
}

sf::CircleShape &Shape::shape()
{
    return circle;
}

void Shape::setFillColorAlpha(unsigned short a)
{
    sf::Color c = circle.getFillColor();
    c.a = a;
    circle.setFillColor(c);
}

void Shape::setOutlineColorAlpha(unsigned short a)
{
    sf::Color c = circle.getOutlineColor();
    c.a = a;
    circle.setOutlineColor(c);
}