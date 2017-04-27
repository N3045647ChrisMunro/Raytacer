#include "Raytracer.h"

#include <iostream>

#include "Image.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "Shape.h"
#include "Light.h"
#include "Colour.h"
#include "Sphere.h"
#include "Plane.h"

Raytracer::Raytracer()
{
    //ctor
}

Raytracer::~Raytracer()
{
    //dtor
}

bool Raytracer::renderScene(Scene *scene, Image *image, std::string filepath, const int startIDX_X,
                            const int startIDX_Y, const int endIDX_X, const int endIDX_Y)
{
    try{
        std::cout << "Rendering..." << std::endl;

        //int antiAliasedSampling = 2;

        int x = startIDX_X;
        int y = startIDX_Y;

        for(x = 0; x < endIDX_X; x++){
            for(y = 0; y < endIDX_Y; y++){

                const float u = (2.0f * x) / image->getWidth() - 1.0f;
                const float v = (-2.0f * y) / image->getHeight() + 1.0f;

                Ray ray;
                Camera *mainCamera = scene->getCamera();
                ray = mainCamera->generateRay(u, v);

                RayHitData rayHitData;
                rayHitData.ray = ray;

                std::vector<Shape*> objects = scene->getAllObjects();
                std::vector<Light*> lights = scene->getAllLights();

                //std::cout << objects.size() << std::endl;

                if(objects.size() > 0){

                    for(unsigned int i = 0; i < objects.size(); i++){

                        if(objects[i]->checkForIntersection(rayHitData)){

                            Colour col = rayHitData.colour;
                            image->set(x, y, col);

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

                            }*/                   }

                    }
                }

            }
        }

        image->saveImage(filepath.c_str());

        std::cout << "Done." << std::endl;
    }
    catch(std::exception& e){
        std::cerr << "Rendering Failed: Exception Occurred: " << e.what() << std::endl;
    }



}
