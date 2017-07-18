#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <string>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "GL/RedGL.hpp"

typedef struct Vertex
{
    float Position_x;
    float Position_y;
    float Position_z;

    float Normal_x;
    float Normal_y;
    float Normal_z;

    float TexCoords_x;
    float TexCoords_y;
}Vertex;

typedef struct Texture
{
    GLuint id;
    std::string type;
}Texture;

class Mesh
{
private:
    GLVAO * vao;
    std::vector<Vertex*> * vertices;
    std::vector<GLuint> * indices;
    std::vector<Texture*> * textures;

    float * arrayVertices;
    float * arrayNormals;
    float * arrayTxtcoor;

    unsigned int * arrayIndices;
public:
    Mesh(std::vector<Vertex*> * vertices, std::vector<GLuint> * indices, std::vector<Texture*> * textures);
    ~Mesh();

    void Draw(GLProgram * program);
};

class Model
{
private:
    std::vector<Mesh*> * meshs;
public:
    Model(std::string path);
    ~Model();

    void Draw(GLProgram * program);
};
