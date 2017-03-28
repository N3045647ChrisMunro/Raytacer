//
//  Light.h
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 25/03/2017.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#pragma once

#include "Vector3D.h"
#include "Colour.h"

class Light
{
    public:
        Light();
        Light(Vector3D position, Colour lightColour);
        ~Light();

        Vector3D getPosition() const { return position_; }
        Colour getColour() const { return colour_; }

    private:

        Vector3D position_;
        Colour colour_;

};

