//
//  main.cpp
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 15/02/2017.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#include <iostream>
#include "Vector3D.h"
#include "Ray.h"
#include "Camera.h"
#include "Colour.h"
#include "Image.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"
#include "Plane.h"
#include "RayHitData.hpp"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    Colour col1(153, 230, 255);
    Colour col2(255, 0, 0);

    Colour col3(col1 + col2);

    const int width = 1080;
    const int height = 720;
    Image image(width, height, Colour(0, 0, 0));

    Vector3D cameraPosition(0.f, 10.0f, 10.f);
    Vector3D lookAt(0.f, 10.0f, 0.f);
    float aspectRatio = (float)width / (float)height;

    Camera *mainCamera = new Camera(cameraPosition, lookAt, Vector3D(0.f, 1.f, 0.f), 3.14159 / 4, aspectRatio);
    Scene *scene = new Scene();

    Colour col4(0, 0, 0);
    Sphere *sphere = new Sphere(Vector3D(20.0f, 10.0f, -50.f), 10.0f, col2);
    Sphere *sphere2 = new Sphere(Vector3D(-30.0, 10.0, -50.0), 10.f, Colour(0, 0, 255));
    Sphere *sphere3 = new Sphere(Vector3D(0.0, 20.0, -75.0), 20.f, Colour(156, 255, 78));

    Plane *groundPlane = new Plane(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.f), Colour(114, 106, 67));

    Vector3D lightPos(0.f, 20.f, 10.f);
    Vector3D lightDir = lightPos - Vector3D(0.0, 0.0, 0.0);
    Light *light = new Light(lightPos, lightDir, Colour(255, 255, 255));

    scene->setSceneCamera(mainCamera);
    scene->addObject(groundPlane);
    scene->addObject(sphere);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addLight(light);

    std::cout << "Rendering..." << std::endl;

    int antiAliasedSampling = 2;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){

            const float u = (2.0f * x) / width - 1.0f;
            const float v = (-2.0f * y) / height + 1.0f;

            Ray ray;
            ray = mainCamera->generateRay(u, v);

            RayHitData rayHitData;
            rayHitData.ray = ray;

            std::vector<Shape*> objects = scene->getAllObjects();
            std::vector<Light*> lights = scene->getAllLights();

            //std::cout << objects.size() << std::endl;

            if(objects.size() > 0){

                for(unsigned int i = 0; i < objects.size(); i++){

                    if(objects[i]->checkForIntersection(rayHitData)){

                        col4 = rayHitData.colour;
                        image.set(x, y, col4);

                        /*for(unsigned int j = 0; j < lights.size(); j++){

                            Vector3D intersectionPoint = ray.calculatePointOnRay(rayHitData.t);
                            Vector3D shadowRayDirection = lights[j]->getPosition() - intersectionPoint;
                            float distToLight = shadowRayDirection.magnitude();
                            shadowRayDirection = shadowRayDirection.normalize();

                            Vector3D intersectNormal = rayHitData.shape->getNormalAtPoint(intersectionPoint);

                            bool shadowed = false;

                            RayHitData shadowHitData;

                            Ray shadowRay(intersectionPoint * 0.0001, shadowRayDirection);

                            shadowHitData.ray = shadowRay;

                        }*/
                    }

                }
            }

        }
    }

    image.saveImage("test.bmp");

    std::cout << "Done." << std::endl;

    return 0;
}
