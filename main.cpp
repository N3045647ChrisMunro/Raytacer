//
//  main.cpp
//  Raytracer
//
//  Created by MUNRO, CHRISTOPHER on 15/02/2017.
//  Copyright � 2017 MUNRO, CHRISTOPHER. All rights reserved.
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
#include "Raytracer.h"


#include "tinyXML/tinyxml.h"

using namespace std;

void serializeScene(Scene *scene, std::string filename);
Scene* loadSceneDataFromXml(std::string filepath);

int main()
{
    Colour col1(153, 230, 255);
    Colour col2(255, 0, 0);

    Colour col3(col1 + col2);

    const int width = 1080;
    const int height = 720;
    Image *image = new Image(width, height, Colour(0, 0, 0));

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

    //serializeScene(scene, "Scene.xml");
    //scene = loadSceneDataFromXml("Scene.xml");

    Raytracer *rayTracer = new Raytracer();

    rayTracer->renderScene(scene, image, "test1.bmp", 0, 0, image->getWidth(), image->getHeight());

    return 0;
}

// Serialize All Scene Data to a XML file
void serializeScene(Scene *scene, std::string filename)
{
    Camera *camera = scene->getCamera();
    std::vector<Shape*> sceneObjects = scene->getAllObjects();
    std::vector<Light*> sceneLights = scene->getAllLights();

    // Create a new XML Document
    TiXmlDocument xmlDoc;
    TiXmlElement *nodeData;

    // XML Version declaration statement
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "","");
    xmlDoc.LinkEndChild(decl);

    // Create Root Node
    TiXmlElement *rootNode = new TiXmlElement("Scene");
    xmlDoc.LinkEndChild(rootNode);

    // Add a Comment
    TiXmlComment *comment = new TiXmlComment();
    comment->SetValue("Scene Contents and Information");
    rootNode->LinkEndChild(comment);

    // Add a camera Node
    TiXmlElement *cameraNode = new TiXmlElement("Camera");
    rootNode->LinkEndChild(cameraNode);

    // Add all data concerning the Camera;
    // ****Position
    nodeData = new TiXmlElement("Position");
    nodeData->SetDoubleAttribute("x", camera->getPosition().x);
    nodeData->SetDoubleAttribute("y", camera->getPosition().y);
    nodeData->SetDoubleAttribute("z", camera->getPosition().z);
    cameraNode->LinkEndChild(nodeData);

    // ****Direction
    nodeData = new TiXmlElement("Direction");
    nodeData->SetDoubleAttribute("x", camera->getDirection().x);
    nodeData->SetDoubleAttribute("y", camera->getDirection().y);
    nodeData->SetDoubleAttribute("z", camera->getDirection().z);
    cameraNode->LinkEndChild(nodeData);

    // ****UpVector
    nodeData = new TiXmlElement("UpVector");
    nodeData->SetDoubleAttribute("x", camera->getUpVector().x);
    nodeData->SetDoubleAttribute("y", camera->getUpVector().y);
    nodeData->SetDoubleAttribute("z", camera->getUpVector().z);
    cameraNode->LinkEndChild(nodeData);

    // ****RightVector
    nodeData = new TiXmlElement("RightVector");
    nodeData->SetDoubleAttribute("x", camera->getRightVector().x);
    nodeData->SetDoubleAttribute("y", camera->getRightVector().y);
    nodeData->SetDoubleAttribute("z", camera->getRightVector().z);
    cameraNode->LinkEndChild(nodeData);

    // ****Width & Height
    nodeData = new TiXmlElement("Dimensions");
    nodeData->SetDoubleAttribute("Width", camera->getWidth());
    nodeData->SetDoubleAttribute("Height", camera->getHeight());
    cameraNode->LinkEndChild(nodeData);

    // Add a Objects node if objects exist
    if(sceneObjects.size() > 0){

        TiXmlElement *objectsNode = new TiXmlElement("Objects");
        rootNode->LinkEndChild(objectsNode);

        // Loop all objects adding in their data to the xml Document
        for(unsigned int i = 0; i < sceneObjects.size(); i++){

            // Check to see what type the Object is
            if(sceneObjects[i]->getType() == "Sphere"){

                TiXmlElement *newSphere = new TiXmlElement("Sphere");
                objectsNode->LinkEndChild(newSphere);

                // Add Position
                nodeData = new TiXmlElement("Position");
                nodeData->SetDoubleAttribute("x", sceneObjects[i]->getPosition().x);
                nodeData->SetDoubleAttribute("y", sceneObjects[i]->getPosition().y);
                nodeData->SetDoubleAttribute("z", sceneObjects[i]->getPosition().z);
                newSphere->LinkEndChild(nodeData);

                // Add Radius
                nodeData = new TiXmlElement("Radius");
                nodeData->SetDoubleAttribute("r", sceneObjects[i]->getRadius());
                newSphere->LinkEndChild(nodeData);

                // Add Colour
                nodeData = new TiXmlElement("Colour");
                nodeData->SetAttribute("r", sceneObjects[i]->getColour().r);
                nodeData->SetAttribute("g", sceneObjects[i]->getColour().g);
                nodeData->SetAttribute("b", sceneObjects[i]->getColour().b);
                newSphere->LinkEndChild(nodeData);

            }

            if(sceneObjects[i]->getType() == "Plane"){

                TiXmlElement *newPlane = new TiXmlElement("Plane");
                objectsNode->LinkEndChild(newPlane);

                // Add position
                nodeData = new TiXmlElement("Position");
                nodeData->SetDoubleAttribute("x", sceneObjects[i]->getPosition().x);
                nodeData->SetDoubleAttribute("y", sceneObjects[i]->getPosition().y);
                nodeData->SetDoubleAttribute("z", sceneObjects[i]->getPosition().z);
                newPlane->LinkEndChild(nodeData);

                // Add Normal
                nodeData = new TiXmlElement("Normal");
                nodeData->SetDoubleAttribute("x", sceneObjects[i]->getNormal().x);
                nodeData->SetDoubleAttribute("y", sceneObjects[i]->getNormal().y);
                nodeData->SetDoubleAttribute("z", sceneObjects[i]->getNormal().z);
                newPlane->LinkEndChild(nodeData);

                // Add Colour
                nodeData = new TiXmlElement("Colour");
                nodeData->SetAttribute("r", sceneObjects[i]->getColour().r);
                nodeData->SetAttribute("g", sceneObjects[i]->getColour().g);
                nodeData->SetAttribute("b", sceneObjects[i]->getColour().b);
                newPlane->LinkEndChild(nodeData);

            }
        }

    }

    // Add Lights if they exist
    if(sceneLights.size() > 0){

        TiXmlElement *lightNode = new TiXmlElement("Lights");
        rootNode->LinkEndChild(lightNode);

        for(unsigned int i = 0; i < sceneLights.size(); i++){

            TiXmlElement *newLight = new TiXmlElement("Light");
            lightNode->LinkEndChild(newLight);

            // Add Position
            nodeData = new TiXmlElement("Position");
            nodeData->SetDoubleAttribute("x", sceneLights[i]->getPosition().x);
            nodeData->SetDoubleAttribute("y", sceneLights[i]->getPosition().y);
            nodeData->SetDoubleAttribute("z", sceneLights[i]->getPosition().z);
            newLight->LinkEndChild(nodeData);

            // Add Colour
            nodeData = new TiXmlElement("Colour");
            nodeData->SetAttribute("r", sceneLights[i]->getColour().r);
            nodeData->SetAttribute("g", sceneLights[i]->getColour().g);
            nodeData->SetAttribute("b", sceneLights[i]->getColour().b);
            newLight->LinkEndChild(nodeData);

        }
    }

    xmlDoc.SaveFile(filename.c_str());
}

Scene* loadSceneDataFromXml(std::string filepath)
{
    Scene *scene = new Scene();
    Camera *camera = new Camera();
    std::vector<Shape *> objects;
    std::vector<Light *> lights;

    TiXmlDocument xmlDoc(filepath.c_str());
    xmlDoc.LoadFile();

    TiXmlElement *rootNode = xmlDoc.RootElement();
    TiXmlElement *nodeData;

    if(rootNode != nullptr){

        TiXmlElement *cameraNode = rootNode->FirstChildElement("Camera");

        if(cameraNode != nullptr){

            // Read in and set all the needed camera data
            nodeData = cameraNode->FirstChildElement("Position");

            if(nodeData != nullptr){
                double x, y, z;
                nodeData->QueryDoubleAttribute("x", &x);
                nodeData->QueryDoubleAttribute("y", &y);
                nodeData->QueryDoubleAttribute("z", &z);
                camera->setPosition(Vector3D((float)x, (float)y, (float)z));
            }

            nodeData = cameraNode->FirstChildElement("Direction");

            if(nodeData != nullptr){
                double x, y, z;
                nodeData->QueryDoubleAttribute("x", &x);
                nodeData->QueryDoubleAttribute("y", &y);
                nodeData->QueryDoubleAttribute("z", &z);
                camera->setDirection(Vector3D((float)x, (float)y, (float)z));

            }

            nodeData = cameraNode->FirstChildElement("UpVector");

            if(nodeData != nullptr){
                double x, y, z;
                nodeData->QueryDoubleAttribute("x", &x);
                nodeData->QueryDoubleAttribute("y", &y);
                nodeData->QueryDoubleAttribute("z", &z);
                camera->setUpVector(Vector3D((float)x, (float)y, (float)z));

            }

            nodeData = cameraNode->FirstChildElement("RightVector");

            if(nodeData != nullptr){
                double x, y, z;
                nodeData->QueryDoubleAttribute("x", &x);
                nodeData->QueryDoubleAttribute("y", &y);
                nodeData->QueryDoubleAttribute("z", &z);
                camera->setRightVector(Vector3D((float)x, (float)y, (float)z));

            }

            nodeData = cameraNode->FirstChildElement("Dimensions");

            if(nodeData != nullptr){
                double width, height;
                nodeData->QueryDoubleAttribute("Width", &width);
                nodeData->QueryDoubleAttribute("Height", &height);
                camera->setWidth((float)width);
                camera->setHeight((float)height);

            }

            //**** Scene Objects
            TiXmlElement *objectsNode = rootNode->FirstChildElement("Objects");

            if(objectsNode != nullptr){

                //**** Planes
                TiXmlElement *planeNode = objectsNode->FirstChildElement("Plane");

                if(planeNode != nullptr){

                    while(planeNode){

                        Vector3D pos;
                        Vector3D normal;
                        Colour colour;

                        nodeData = planeNode->FirstChildElement("Position");

                        if(nodeData != nullptr){

                            double x, y, z;
                            nodeData->QueryDoubleAttribute("x", &x);
                            nodeData->QueryDoubleAttribute("y", &y);
                            nodeData->QueryDoubleAttribute("z", &z);

                            pos = Vector3D((float)x, (float)y, (float)z);

                        }

                        nodeData = planeNode->FirstChildElement("Normal");

                        if(nodeData != nullptr){

                            double x, y, z;
                            nodeData->QueryDoubleAttribute("x", &x);
                            nodeData->QueryDoubleAttribute("y", &y);
                            nodeData->QueryDoubleAttribute("z", &z);

                            normal = Vector3D((float)x, (float)y, (float)z);

                        }

                        nodeData = planeNode->FirstChildElement("Colour");

                        if(nodeData != nullptr){

                            int r, g, b;
                            nodeData->QueryIntAttribute("r", &r);
                            nodeData->QueryIntAttribute("g", &g);
                            nodeData->QueryIntAttribute("b", &b);

                            colour = Colour(r, g, b);

                        }

                        Plane *tmp = new Plane(pos, normal, colour);
                        objects.push_back(tmp);

                        planeNode = planeNode->NextSiblingElement("Plane");

                    }

                }

                //**** Spheres
                TiXmlElement *sphereNode = objectsNode->FirstChildElement("Sphere");

                if(sphereNode != nullptr){

                    // Read in and set all the needed sphere object data
                    while(sphereNode){

                        //Create a temp sphere object data variables
                        Vector3D pos;
                        float radius;
                        Colour colour;

                        nodeData = sphereNode->FirstChildElement("Position");

                        if(nodeData != nullptr){

                            double x, y, z;
                            nodeData->QueryDoubleAttribute("x", &x);
                            nodeData->QueryDoubleAttribute("y", &y);
                            nodeData->QueryDoubleAttribute("z", &z);

                            pos = Vector3D((float)x, (float)y, (float)z);

                        }

                        nodeData = sphereNode->FirstChildElement("Radius");

                        if(nodeData != nullptr){
                            double r;
                            nodeData->QueryDoubleAttribute("r", &r);

                            radius = (float)r;
                        }

                        nodeData = sphereNode->FirstChildElement("Colour");

                        if(nodeData != nullptr){

                            int r, g, b;
                            nodeData->QueryIntAttribute("r", &r);
                            nodeData->QueryIntAttribute("g", &g);
                            nodeData->QueryIntAttribute("b", &b);

                            colour = Colour(r, g, b);

                        }

                        Sphere *tmp = new Sphere(pos, radius, colour);
                        objects.push_back(tmp);

                        sphereNode = sphereNode->NextSiblingElement("Sphere");
                    }

                }

            }

            //**** Scene Lights
            TiXmlElement *lightsNode = rootNode->FirstChildElement("Lights");

            if(lightsNode != nullptr){

                TiXmlElement *lightNode = lightsNode->FirstChildElement("Light");

                if(lightNode != nullptr){

                    // Read in and set all the needed sphere object data
                    while(lightNode){

                            Vector3D pos;
                            Colour colour;

                            nodeData = lightNode->FirstChildElement("Position");

                            if(nodeData != nullptr){

                                double x, y, z;
                                nodeData->QueryDoubleAttribute("x", &x);
                                nodeData->QueryDoubleAttribute("y", &y);
                                nodeData->QueryDoubleAttribute("z", &z);

                                pos = Vector3D((float)x, (float)y, (float)z);

                            }

                            nodeData = lightNode->FirstChildElement("Colour");

                            if(nodeData != nullptr){

                                int r, g, b;
                                nodeData->QueryIntAttribute("r", &r);
                                nodeData->QueryIntAttribute("g", &g);
                                nodeData->QueryIntAttribute("b", &b);

                                colour = Colour(r, g, b);

                            }

                            Light *tmp = new Light(pos, Vector3D(), colour);

                            lights.push_back(tmp);
                            std::cout << tmp->getPosition();

                            lightNode = lightsNode->NextSiblingElement("Light");

                    }

                }
            }

        }


    }

    scene->setSceneCamera(camera);
    scene->addObjects(objects);
    scene->addLights(lights);

}
