#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>

class Shape {
public:
    Shape(float radius, float points, const sf::Color &fill, const sf::Color &outline, float thickness);
    ~Shape() = default;
private:
    sf::CircleShape circle;
};

#endif // SHAPE_H