#include "Engine/Engine.hpp"

Light::Light()
{
    this->ambient = new float[3];
    this->diffuse = new float[3];
    this->specular = new float[3];
    this->position = new float[3];
}

Light::~Light()
{
    delete ambient;
    delete diffuse;
    delete specular;
    delete position;
}

void Light::UseLight(GLProgram * program)
{
    glUniform3f(program->GetUniformLocation("light.ambient"), ambient[0], ambient[1], ambient[2]);
    glUniform3f(program->GetUniformLocation("light.diffuse"), diffuse[0], diffuse[1], diffuse[2]);
    glUniform3f(program->GetUniformLocation("light.specular"), specular[0], specular[1], specular[2]);
    glUniform3f(program->GetUniformLocation("light.position"),  position[0], position[1], position[2]);
}

void Light::setAmbient(float x,float y,float z)
{
    ambient[0] = x;
    ambient[1] = y;
    ambient[2] = z;
}

void Light::setAmbient(float x)
{
    setAmbient(x,x,x);
}

void Light::setDiffuse(float x,float y,float z)
{
    diffuse[0] = x;
    diffuse[1] = y;
    diffuse[2] = z;
}

void Light::setDiffuse(float x)
{
    setDiffuse(x,x,x);
}

void Light::setSpecular(float x,float y,float z)
{
    specular[0] = x;
    specular[1] = y;
    specular[2] = z;
}

void Light::setSpecular(float x)
{
    setSpecular(x,x,x);
}

void Light::setPosition(float x,float y,float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

void Light::setPosition(float x)
{
    setPosition(x,x,x);
}
