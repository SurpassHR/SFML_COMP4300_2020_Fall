#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <SFML/Graphics.hpp>

class Shape {
public:
    Shape(float radius, float points, const sf::Color &fill, const sf::Color &outline, float thickness);
    Shape(std::shared_ptr<Shape> s);
    ~Shape() = default;
public:
    sf::CircleShape &shape();
    void setFillColorAlpha(unsigned short a);
    void setOutlineColorAlpha(unsigned short a);
private:
    sf::CircleShape circle;
};

#endif // SHAPE_H