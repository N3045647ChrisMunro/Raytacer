
#pragma once

#include "Shape.h"
#include "Vector3D.h"
#include "Colour.h"

class Ray;

class Plane : public Shape
{
    public:
        Plane();
        Plane(const Vector3D& position, const Vector3D& normal, const Colour& colour);
        ~Plane();

        virtual bool checkForIntersection(Ray *ray, Colour& outColour);
        virtual Colour getColour() const { return colour_; }

    private:

        Vector3D position_;
        Vector3D normal_;
        Colour colour_;

};

