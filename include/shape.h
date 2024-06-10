#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics/Shape.hpp>

class Shape : sf::Shape {
public:
    Shape() : sf::Shape() {}
    virtual ~Shape() {}
};

#endif // SHAPE_H
