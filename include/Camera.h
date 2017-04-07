//
//  Camera.h
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 25/03/2017.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#pragma once

#include "Vector3D.h"

class Camera
{
    public:
        Camera();
        Camera(Vector3D position, Vector3D direction, Vector3D bottomVector, Vector3D rightVector);

        ~Camera();

    private:

        Vector3D position_;
        Vector3D direction_;
        Vector3D bottomVector_;
        Vector3D rightVector_;
};
