
#pragma once

#include "Shape.h"
#include "Vector3D.h"
#include "Colour.h"
#include "RayHitData.hpp"

class Ray;

class Plane : public Shape
{
    public:
        Plane();
        Plane(const Vector3D& position, const Vector3D& normal, const Colour& colour);
        ~Plane();

        virtual bool checkForIntersection(RayHitData &rayHitData);
        virtual Colour getColour() const { return colour_; }
        virtual Vector3D getNormalAtPoint(Vector3D point);

    private:

        Vector3D position_;
        Vector3D normal_;
        Colour colour_;

};

