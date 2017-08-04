#pragma once

#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>
#include <vector>
#include <string>

#include <stdint.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "GL/RedGL.hpp"
#include "DEBUG/Debug.hpp"

static int ScreenWidth = 0;
static int ScreenHeight = 0;

typedef struct Vertex
{
    float Position_x;
    float Position_y;
    float Position_z;

    float Normal_x;
    float Normal_y;
    float Normal_z;

    float Tangents_x;
    float Tangents_y;
    float Tangents_z;

    float TexCoords_x;
    float TexCoords_y;
}Vertex;

class Material {
private:
    GLTexture * ambient;
    GLTexture * specular;
    GLTexture * normalMap;
    float shininess;
public:
    Material();
    ~Material();

    void setAmbient(GLTexture * ambient);
    void setSpecular(GLTexture * specular);
    void setNormalMap(GLTexture * normalMap);
    void setShininess(float shininess);

    void UseMaterial(GLProgram * program);
};

class PhongMaterial
{
private:
    GLProgram * phongProgram;
    GLTexture * ambient;
    GLTexture * specular;
    GLTexture * normalMap;
    float shininess;
public:
    PhongMaterial();
    ~PhongMaterial();

    void setAmbient(GLTexture * ambient);
    void setSpecular(GLTexture * specular);
    void setNormalMap(GLTexture * normalMap);
    void setShininess(float shininess);

    void UseMaterial();
};


class PBRMaterial
{
private:
    GLTexture * albedoMap;
    GLTexture * metallicMap;
    GLTexture * roughnessMap;
    GLTexture * normalMap;
    GLTexture * aoMap;
public:
    PBRMaterial();
    ~PBRMaterial();

    void setAlbedoMap(GLTexture * albedoMap);
    void setMetallicMap(GLTexture * metallicMap);
    void setRoughnessMap(GLTexture * roughnessMap);
    void setNormalMap(GLTexture * normalMap);
    void setAoMap(GLTexture * aoMap);

    void UseMaterial();
};

class Mesh
{
private:
    GLVAO * vao;
    std::vector<Vertex*> * vertices;
    std::vector<GLuint> * indices;

    float * arrayVertices;
    float * arrayNormals;
    float * arrayTxtcoor;
    float * tangentsArray;

    unsigned int * arrayIndices;

    Material * material;
public:
    Mesh(std::vector<Vertex*> * vertices, std::vector<GLuint> * indices);
    ~Mesh();

    void setMaterial(Material * material);
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


class PBRLight{
private:
    float * position;
    float * color;
public:
    PBRLight();
    ~PBRLight();

    void setPosition(float x,float y,float z);
    void setColor(float r,float g,float b);

    void UseLight(GLProgram * program,int i);
};

class Light{
private:
    float * ambient;
    float * diffuse;
    float * specular;
    float * position;
public:
    Light();
    ~Light();

    void UseLight(GLProgram * program);

    void setAmbient(float x,float y,float z);
    void setAmbient(float x);

    void setDiffuse(float x,float y,float z);
    void setDiffuse(float x);

    void setSpecular(float x,float y,float z);
    void setSpecular(float x);

    void setPosition(float x,float y,float z);
    void setPosition(float x);
};

class Camera
{
private:
    float * cameraPos;
    float * cameraFront;
    float * cameraUp;

    float width;
    float height;

    float fovy;
    float near;
    float far;
public:
    Camera(float fovy,float width,float height,float near,float far);
    ~Camera();

    void setCamera(float fovy,float width,float height,float near,float far);

    void setCameraPos(float x,float y,float z);
    void setCameraFront(float x,float y,float z);
    void setCameraUp(float x,float y,float z);

    void UseCamera(GLProgram * program);
};
