#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <memory>
#include "components/transform.h"
#include "components/shape.h"
#include "components/collision.h"
#include "components/input.h"
#include "components/score.h"
#include "components/lifespan.h"

class Entity {
public:
    Entity(const std::string tag, int id) : m_tag(tag), m_id(id) {}
    ~Entity() = default;
public:
    // refresh entity position, shape, rotate angle, etc
    void update();
// components
public:
    std::shared_ptr<Transform> transform;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Collision> collision;
    std::shared_ptr<Input> input;
    std::shared_ptr<Score> score;
    std::shared_ptr<Lifespan> lifespan;
// properties
public:
    std::string m_tag{ "default" };
    bool m_active{ true };
    std::size_t m_id{ 0 };
};

#endif // ENTITY_H