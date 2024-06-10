#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML/Graphics/Transform.hpp>

class Transform : public sf::Transform {
public:
    Transform() : sf::Transform() {}
    virtual ~Transform() {}
};

#endif // TRANSFORM_H
