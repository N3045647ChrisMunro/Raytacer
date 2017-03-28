#include "Camera.h"

Camera::Camera()
{
    //ctor
    position_ = Vector3D(0.f, 0.f, 0.f);
    direction_ = Vector3D(0.f, 0.f, 1.f);
    bottomVector_ = Vector3D(0.f, 0.f, 0.f);
    rightVector_ = Vector3D(0.f, 0.f, 0.f);
}

Camera::Camera(Vector3D position, Vector3D direction, Vector3D bottomVector, Vector3D rightVector) :
               position_(position), direction_(direction), bottomVector_(bottomVector), rightVector_(rightVector)
{

}

Camera::~Camera()
{
    //dtor
}
