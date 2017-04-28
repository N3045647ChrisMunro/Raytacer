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
#include <limits>

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

        bool isShadow = false;
        Shape *tmpShape = new Shape();

        float invWidth = 1 / (float)image->getWidth();
        float invHeight = 1 / (float)image->getHeight();

        float fov = 30;
        float aspectRatio = image->getWidth() / (float)image->getHeight();
        float angle = tan(3.14159 * 0.5 * fov / 180);

        for(x = 0; x < endIDX_X; x++){
            for(y = 0; y < endIDX_Y; y++){

                const float u = (2.0f * x) / image->getWidth() - 1.0f;
                const float v = (-2.0f * y) / image->getHeight() + 1.0f;

                Ray ray;
                Camera *mainCamera = scene->getCamera();
                ray = mainCamera->generateRay(u, v);

                RayHitData rayHitData;
                rayHitData.ray = ray;

                Vector3D intersectionPoint;
                Vector3D intersectNormal;

                Vector3D lightDirection;


                float minDistance = std::numeric_limits<float>::infinity();

                std::vector<Shape*> objects = scene->getAllObjects();
                std::vector<Light*> lights = scene->getAllLights();

                //std::cout << objects.size() << std::endl;


                if(objects.size() > 0){

                    for(unsigned int i = 0; i < objects.size(); i++){

                        if(objects[i]->checkForIntersection(rayHitData)){

                            //std::cout << objects[i]->getType() << std::endl;
                            intersectionPoint = ray.calculatePointOnRay(rayHitData.t);
                            intersectNormal = objects[i]->getNormalAtPoint(intersectionPoint);


                            float dist = distance(mainCamera->getPosition(), intersectionPoint);

                            if(dist < minDistance){
                                tmpShape = objects[i];
                                minDistance = dist;
                            }

                            if(tmpShape != nullptr){

                                lightDirection = Vector3D(10.0, 40.0, -80.0) - intersectionPoint;
                                Vector3D shadowRayDirection = Vector3D(10.0, 40.0, -70.0) - intersectionPoint;

                                Ray shadowRay(intersectionPoint * 0.0001, -shadowRayDirection);
                                RayHitData shadowRayHitData;
                                shadowRayHitData.ray = shadowRay;

                                for(unsigned int i = 0; i < objects.size(); i++){

                                    if(objects[i]->checkForIntersection(shadowRayHitData)){
                                        std::cout << "T" << std::endl;
                                        //isShadow = true;
                                        break;
                                    }

                                }


                                if(!isShadow){
                                    Colour col = (Colour(255, 255, 255) * dotProduct(intersectNormal.normalize(), lightDirection.normalize()) * (tmpShape->getColour()*1.0f));
                                    col = col / 255;
                                    //std::cout << col;
                                    col.clamp();
                                    image->set(x, y, col);
                                }
                                else{
                                    Colour col = tmpShape->getColour() * 0.10f;
                                    image->set(x, y, col);
                                }

                            }

                        }
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

/*


                            Ray shadowRay(intersectionPoint, shadowRayDirection);

                            bool isShadow = false;

                            for()

                            for(unsigned int j = 0; j < lights.size(); j++){


                                float distToLight = shadowRayDirection.magnitude();
                                shadowRayDirection = shadowRayDirection.normalize();

                                Vector3D intersectNormal = rayHitData.shape->getNormalAtPoint(intersectionPoint);

                                bool shadowed = false;

                                RayHitData shadowHitData;

                                Ray shadowRay(intersectionPoint * 0.0001, shadowRayDirection);

                                shadowHitData.ray = shadowRay;

                            }
*/
