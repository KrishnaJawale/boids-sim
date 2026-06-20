#pragma once
#include "Vec2.h"

struct Boid {
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    Boid(Vec2 position, Vec2 velocity, Vec2 acceleration) : position(position), velocity(velocity), acceleration(acceleration) {}
};