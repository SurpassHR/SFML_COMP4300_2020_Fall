#include "entity.h"
#include "utils.h"

void Entity::update()
{
    // position
    if (shape == nullptr) {
        LOG("%s shape nullptr err", m_tag.c_str());
        return;
    }
    shape->shape().setPosition(transform->pos.vec2f() + transform->currVelocity.vec2f());

    if (transform == nullptr) {
        LOG("%s transform nullptr err", m_tag.c_str());
        return;
    }
    transform->pos = shape->shape().getPosition();

    // angle
    shape->shape().rotate(transform->angle);
}