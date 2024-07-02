#include "entity.h"

void Entity::update()
{
    // position
    transform->pos = shape->shape().getPosition();
    shape->shape().setPosition(transform->pos.vec2f() + transform->currVelocity.vec2f());

    // angle
    shape->shape().rotate(transform->angle);
}