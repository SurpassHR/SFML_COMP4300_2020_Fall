#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <memory>
#include "vec2.h"

class Transform {
public:
    Transform(const Vec2 &pos, const Vec2 &velocity, float angle) :
        pos(pos), velocity(velocity), angle(angle) {}
    Transform(std::shared_ptr<Transform> t)
        : pos(t->pos),
        velocity(t->velocity),
        currVelocity(t->currVelocity),
        scale(t->scale),
        angle(t->angle) {}
    ~Transform() = default;
public:
    Vec2 pos{ 0.0f, 0.0f };
    Vec2 velocity{ 0.0f, 0.0f };
    Vec2 currVelocity{ 0.0f, 0.0f };
    Vec2 scale{ 0.0f, 0.0f };
    float angle{ 0.0f };
};

#endif // TRANSFORM_H