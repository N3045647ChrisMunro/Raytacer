//
//  Sphere.h
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 25/03/2017.
//  Copyright � 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#pragma once

#include "Shape.h"
#include "Vector3D.h"
#include "Colour.h"
#include "RayHitData.hpp"

class Ray;

class Sphere : public Shape
{
    public:
        Sphere();
        Sphere(Vector3D centerPosition, float radius, Colour colour);
        ~Sphere();

        float getRadius() const { return radius_; }
        Vector3D getPosition() const { return position_; }
        virtual Colour getColour() const;
        virtual Vector3D getNormalAtPoint(Vector3D point);

        virtual bool checkForIntersection(RayHitData &rayHitData);

    private:

        Vector3D position_;
        float radius_;
        Colour colour_;

};
