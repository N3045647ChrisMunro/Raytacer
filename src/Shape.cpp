//
//  Shape.cpp
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 25/03/2017.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//
#include "Shape.h"

#include "Ray.h"
#include "Colour.h"

Shape::Shape()
{
    //ctor
}

Shape::~Shape()
{
    //dtor
}

bool Shape::checkForIntersection(Ray *ray, Colour& outColour)
{
    return false;
}

Colour Shape::getColour() const
{

}
