#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec2.h"

class Transform {
public:
    Vec2 pos{ 0.0f, 0.0f };
    Vec2 speed{ 0.0f, 0.0f };
    Vec2 scale{ 0.0f, 0.0f };
    Vec2 angle{ 0.0f, 0.0f };
};

#endif // TRANSFORM_H