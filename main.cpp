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
#include "Scene.h"
#include "Plane.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    Colour col1(153, 230, 255);
    Colour col2(255, 0, 0);

    Colour col3(col1 + col2);

    const int width = 1080;
    const int height = 720;
    Image image(width, height, Colour(89, 89, 89));

    Vector3D cameraPosition(0.f, 5.f, -10.f);
    Vector3D lookAt(0.f, 0.0f, 0.f);
    float aspectRatio = (float)width / (float)height;

    Camera *mainCamera = new Camera(cameraPosition, lookAt, Vector3D(0.f, 1.f, 0.f), 3.14159 / 4, aspectRatio);
    Scene *scene = new Scene();

    Colour col4(0, 0, 0);
    Sphere *sphere = new Sphere(Vector3D(0.0f, 0.0f, 500.0f), 50.0f, col2);
    Sphere *sphere2 = new Sphere(Vector3D(150.0, 0.0, 250.0), 50.f, Colour(0, 0, 255));

    Plane* groundPlane = new Plane(Vector3D(0.0f, -1.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.f), Colour(114, 106, 67));

    //scene->addObject(sphere2);
    scene->addObject(groundPlane);
    scene->addObject(sphere);

    std::cout << "Rendering..." << std::endl;

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){

            const float u = (2.0f * x) / width - 1.0f;
            const float v = (-2.0f * y) / height + 1.0f;

            Ray ray;
            ray = mainCamera->generateRay(u, v);

            std::vector<Shape*> objects = scene->getAllObjects();

            //std::cout << objects.size() << std::endl;

            if(objects.size() > 0){

                for(unsigned int i = 0; i < objects.size(); i++){

                    if(objects[i]->checkForIntersection(&ray, col4)){
                        col4 = objects[i]->getColour();
                        image.set(x, y, col4);
                    }else{
                        //image.set(x, y, Colour(89, 89, 89));
                    }

                    //std::cout << "I: " << i << std::endl;

                }
            }

        }
    }

    image.saveImage("test.bmp");

    std::cout << "Done." << std::endl;

    return 0;
}
