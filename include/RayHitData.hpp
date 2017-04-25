#pragma once

#include "Ray.h"
#include "Colour.h"
#include "Shape.h"

class Shape;

struct RayHitData
{
    Ray ray;
    Shape *shape;
    Colour colour;

    float t;

    RayHitData();
};

inline RayHitData::RayHitData()
{
    ray = Ray();
    shape = nullptr;
    colour = Colour();

    t = ray.getMaxDistance();
}
