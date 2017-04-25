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
        Light(Vector3D position, Vector3D direction, Colour lightColour);
        ~Light();

        Vector3D getPosition() const { return position_; }
        Vector3D getDirection() const { return direction_; }
        Colour getColour() const { return colour_; }

    private:

        Vector3D position_;
        Vector3D direction_;
        Colour colour_;

};

