//
//  Scene.h
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 25/03/2017.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#pragma once

#include <vector>

class Camera;
class Shape;
class Light;

class Scene
{
    public:
        Scene();
        ~Scene();

        void setSceneCamera(Camera *camera);
        void addObject(Shape *object);
        void addLight(Light* light);

        std::vector<Shape *> getAllObjects() const { return objects_; }
        std::vector<Light *> getAllLights() const { return lights_; }


    private:

        Camera *sceneCamera_ = nullptr;

        std::vector<Shape*> objects_;
        std::vector<Light*> lights_;

};

