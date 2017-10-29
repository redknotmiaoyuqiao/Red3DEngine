#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Engine{
public:
    void Start();
    void Update();
    void End();
};

class RedEyeBehaviour{
public:
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void End() = 0;
};

class Screen{
private:
    Screen();
    static Screen * m_pInstance;
    int ScreenWidth = 0;
    int ScreenHeight = 0;
public:
    static Screen * getInstance();

    void setWidthAndHeight(int width,int height);

    int getWidth();
    int getHeight();
};

class Input
{
private:
    Input();

    static Input * m_pInstance;

    glm::vec2 mousePoint;

public:
    bool keys[1024];

public:
    static Input * getInstance();

    void setMousePoint(float x,float y);
    glm::vec2 getMousePoint();
};



typedef struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 texcoord;
}Vertex;

class Mesh
{
private:
    float * arrayVertices;
    float * arrayNormals;
    float * arrayTxtcoor;
    float * tangentsArray;
public:
    Mesh(float * arrayVertices,float * arrayNormals,float * arrayTxtcoor,float * tangentsArray);
    ~Mesh();
};

class Model{
private:
    std::vector<Mesh*> * meshs;
public:
    Model(std::string path);
    ~Model();
};

