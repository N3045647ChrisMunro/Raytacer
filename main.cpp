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

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    Colour col1(153, 230, 255);
    Colour col2(255, 0, 0);

    Colour col3(col1 + col2);


    Image image(800, 600, Colour(89, 89, 89));

    Vector3D cameraPosition(0, 1.5, -5);
    Vector3D lookAt(0.f, 0.f, 0.f);
    Vector3D cameraDirection = cameraPosition - lookAt;

    cameraDirection = cameraDirection.normalize(-cameraDirection);


    Camera *mainCamera = new Camera();
    Scene *scene = new Scene();

    Colour col4(0, 0, 0);
    Sphere *sphere = new Sphere(Vector3D(400, 300, 1000), 50.f, col2);
    Sphere *sphere2 = new Sphere(Vector3D(400, 200, 1000), 50.f, Colour(0, 0, 255));
    Sphere *sphere3 = new Sphere(Vector3D(400, 100, 1000), 50.f, Colour(0, 0, 255));
    Sphere *sphere4 = new Sphere(Vector3D(400, 400, 1000), 50.f, Colour(0, 0, 255));

    Sphere *sphere5 = new Sphere(Vector3D(600, 200, 1000), 50.f, Colour(0, 0, 255));
    Sphere *sphere6 = new Sphere(Vector3D(600, 100, 1000), 50.f, Colour(0, 0, 255));
    Sphere *sphere7 = new Sphere(Vector3D(600, 400, 1000), 50.f, Colour(0, 0, 255));

    scene->addObject(sphere);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);

    scene->addObject(sphere5);
    scene->addObject(sphere6);
    scene->addObject(sphere7);

    std::cout << "Rendering..." << std::endl;

    for(int y = 0; y < 600; y++){
        for(int x = 0; x < 800; x++){

            Ray *ray = new Ray(Vector3D(x, y, 0), Vector3D(0, 0, -1));

            std::vector<Shape*> objects = scene->getAllObjects();

            //std::cout << objects.size() << std::endl;

            if(objects.size() > 0){

                for(unsigned int i = 0; i < objects.size(); i++){

                    if(objects[i]->checkForIntersection(ray, col4)){
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
