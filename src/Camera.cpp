#include "Camera.h"

#include <cmath>

Camera::Camera()
{
    //ctor
    position_ = Vector3D(0.f, 0.f, 0.f);
    direction_ = Vector3D(0.f, 0.f, 1.f);
    upVector_ = Vector3D(0.f, 0.f, 0.f);
    rightVector_ = Vector3D(0.f, 0.f, 0.f);
}

Camera::Camera(Vector3D position, Vector3D target, Vector3D upVector, const float fieldOfView, const float aspectRatio) :
               position_(position)
{

    direction_ = (target - position);
    direction_ = direction_.normalize();

    rightVector_ = rightVector_.crossProduct(direction_, upVector);
    rightVector_ = rightVector_.normalize();
    upVector_ = upVector.crossProduct(rightVector_, direction_);

    height_ = tan(fieldOfView);
    width_ = height_ * aspectRatio;
}

Camera::~Camera()
{
    //dtor
}

Ray Camera::generateRay(float u, float v)
{
    Vector3D rayDirection = direction_ + u * width_ * rightVector_ + v * height_ * upVector_;

    //std::cout << rayDirection << std::endl;

    return Ray(position_, rayDirection);


}
