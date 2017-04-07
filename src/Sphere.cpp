//
//  Sphere.h
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 25/03/2017.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#include "Sphere.h"

#include <iostream>
#include "Ray.h"

Sphere::Sphere()
{
    //ctor
}

Sphere::Sphere(Vector3D centerPosition, float radius, Colour colour) : position_(centerPosition), radius_(radius), colour_(colour)
{

}

Sphere::~Sphere()
{
    //dtor
}

bool Sphere::checkForIntersection(Ray *ray, Colour& outColour)
{
    const Vector3D rayOrigin = ray->getRayOrigin();
    const Vector3D rayDirection = ray->getRayDirection();


    Vector3D distanceToSphere = rayOrigin - position_;

    Vector3D temp;

    float A = temp.dotProduct(rayDirection, rayDirection);
    float B = temp.dotProduct(rayDirection, distanceToSphere) * 2;
    double C = temp.dotProduct(distanceToSphere, distanceToSphere) - radius_ * radius_;

    //std::cout << "A: " << A << " B: " << B << " C: "<< C << std::endl;

    float discriminant = B * B - 4 * A * C;

    if(discriminant > 0){
        return true;
    }

    return false;
}

Colour Sphere::getColour() const
{
    return colour_;
}


