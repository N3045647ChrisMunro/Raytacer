#include "Light.h"

Light::Light()
{
    //ctor
    //Default to the centre of the 'World'
    position_ = Vector3D(0.f, 0.f, 0.f);

    //Default to white
    colour_ = Colour(255.f, 255.f, 255.f);
}

Light::Light(Vector3D position, Colour lightColour) : position_(position), colour_(lightColour)
{

}

Light::~Light()
{
    //dtor
}


