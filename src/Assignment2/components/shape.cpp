#include "shape.h"

Shape::Shape(float radius, float points, const sf::Color &fill, const sf::Color &outline, float thickness)
    : circle(radius, points)
{
    circle.setFillColor(fill);
    circle.setOutlineColor(outline);
    circle.setOutlineThickness(thickness);
}
