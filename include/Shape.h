//
//  Shape.h
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 25/03/2017.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#pragma once

class Ray;
class Colour;

class Shape
{
    public:
        Shape();
        virtual ~Shape();

        virtual bool checkForIntersection(Ray *ray, Colour& outColour);
        virtual Colour getColour() const;

    private:
};

