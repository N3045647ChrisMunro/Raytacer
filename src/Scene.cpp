//
//  Scene.cpp
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#include "Scene.h"

#include "Camera.h"
#include "Shape.h"
#include "Light.h"

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    //dtor
    //Free up the memory, consumed by the scene components
    delete sceneCamera_;

    for(unsigned int i = 0; i < objects_.size(); i++){
        delete objects_[i];
    }

    for(unsigned int i = 0; i < lights_.size(); i++){
        delete lights_[i];
    }

}

void Scene::setSceneCamera(Camera *camera)
{
    sceneCamera_ = camera;
}

void Scene::addObject(Shape *shape)
{
    objects_.push_back(shape);
}

void Scene::addLight(Light *light)
{
    lights_.push_back(light);
}
