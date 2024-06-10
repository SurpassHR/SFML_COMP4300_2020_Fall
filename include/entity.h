#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "shape.h"
#include "transform.h"
#include "name.h"
#include "bounding_box.h"

class Entity {
public:
    Entity(sf::Vector2f pos, sf::Vector2f velocity) : m_pos(pos), m_velocity(velocity) {}
    virtual ~Entity() {}
public:
    // getters and setters
    sf::Vector2f Pos() const { return m_pos; }
    void SetPos(const sf::Vector2f &pos) { m_pos = pos; }
    sf::Vector2f Velocity() const { return m_velocity; }
    void SetVelocity(const sf::Vector2f &velocity) { m_velocity = velocity; }

    std::shared_ptr<sf::Shape> Shape() const { return m_shape; }
    void SetShape(std::shared_ptr<sf::Shape> shape) { m_shape = shape; }
    std::shared_ptr<sf::Transform> Transform() const { return m_transform; }
    std::shared_ptr<sf::Text> Name() const { return m_name; }
    std::shared_ptr<BoundingBox> BBox() const { return m_bBox; }
private:
    // components
    sf::Vector2f m_pos{ 0.0f, 0.0f };
    sf::Vector2f m_velocity{ 0.0f, 0.0f };

    std::shared_ptr<sf::Shape> m_shape;
    std::shared_ptr<sf::Transform> m_transform;
    std::shared_ptr<sf::Text> m_name;
    std::shared_ptr<BoundingBox> m_bBox;
};

#endif // ENTITY_H
