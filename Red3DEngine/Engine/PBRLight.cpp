#include "Engine/Engine.hpp"

PBRLight::PBRLight()
{
    this->position = new float[3];
    this->color = new float[3];
}

PBRLight::~PBRLight()
{
    delete this->position;
    delete this->color;
}

void PBRLight::setPosition(float x,float y,float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

void PBRLight::setColor(float r,float g,float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void PBRLight::UseLight(GLProgram * program,int i)
{
    const char * position_str = ("lightPositions[" + std::to_string(i) + "]").c_str();
    const char * color_str = ("lightColors[" + std::to_string(i) + "]").c_str();

    //RedLog("%s\n",color_str);

    glUniform3f(program->GetUniformLocation((char *)position_str), position[0], position[1], position[2]);
    glUniform3f(program->GetUniformLocation((char *)color_str), color[0], color[1], color[2]);
}
