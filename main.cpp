//
//  main.cpp
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 15/02/2017.
//  Copyright © 2017 MUNRO, CHRISTOPHER. All rights reserved.
//

#include <iostream>
#include "Vector3D.h"
#include "Colour.h"
#include "Image.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    Colour col1(255, 0, 0);
    Colour col2(10, 10, 10);

    Colour col3(col1 + col2);

    std::cout << col1 << std::endl;
    std::cout << col2 << std::endl;
    std::cout << col3 << std::endl;

    Image image(800, 600, col2);

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
