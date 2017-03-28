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

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    Colour col1(153, 230, 255);
    Colour col2(89, 89, 89);

    Colour col3(col1 + col2);

    std::cout << col1 << std::endl;
    std::cout << col2 << std::endl;
    std::cout << col3 << std::endl;

    Image image(800, 600, col2);

    Vector3D cameraPosition(0, 1.5, -5);
    Vector3D lookAt(0.f, 0.f, 0.f);
    Vector3D cameraDirection = cameraPosition - lookAt;

    std::cout << cameraDirection << std::endl;

    cameraDirection = cameraDirection.normalize(-cameraDirection);

    std::cout << cameraDirection << std::endl;

    Camera *mainCamera = new Camera();

    for(int y = 0; y < 600; y++){
        for(int x = 0; x < 800; x++){

            if(x > 200 && x < 600 && y > 20 && y < 580){

                image.set(x, y, col1);

            }

        }
    }

    image.saveImage("test.bmp");

    return 0;
}
