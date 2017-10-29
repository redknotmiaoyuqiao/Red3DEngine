#include "Component/Component.hpp"

Light::Light()
{

}

Light::~Light()
{

}

void Light::setPosition(float x,float y,float z)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

void Light::setColor(float r,float g,float b)
{
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
}

glm::vec3 Light::getPosition()
{
    return this->position;
}

glm::vec3 Light::getColor()
{
    return this->color;
}
