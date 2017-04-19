#include "Plane.h"
#include "Ray.h"

Plane::Plane()
{
    //ctor
}

Plane::Plane(const Vector3D& position, const Vector3D& normal, const Colour& colour) : position_(position), normal_(normal), colour_(colour)
{

}

Plane::~Plane()
{
    //dtor
}

bool Plane::checkForIntersection(Ray *ray, Colour& outColour)
{
    Vector3D temp;
    float dn = dotProduct(ray->getRayDirection(), normal_);

    if(dn != 0.0f)
        return true;

    return false;
}
