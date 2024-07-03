#include "entity.h"

void Entity::update()
{
    // position
    shape->shape().setPosition(transform->pos.vec2f() + transform->currVelocity.vec2f());
    transform->pos = shape->shape().getPosition();

    // angle
    shape->shape().rotate(transform->angle);
}