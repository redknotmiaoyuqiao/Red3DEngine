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

#include "Struct.hpp"

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

    void UseMaterial(GLProgram * program);
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
public:
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

    void setCameraWidthHeight(float width,float height);

    void setCameraPos(float x,float y,float z);
    void setCameraFront(float x,float y,float z);
    void setCameraUp(float x,float y,float z);

    void UseCamera(GLProgram * program);
    void UseCameraInSky(GLProgram * program);
};

class SkyBox
{
private:
    GLCubeMapTexture * cubMap;
    GLVAO * skyVAO;
public:
    SkyBox();
    ~SkyBox();

    void loadTexture(vector<std::string> * faces);

    void UseSkyBox(GLProgram * gragram,Camera * camera);
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

    Vector2 mousePoint;

public:
    bool keys[1024];

public:
    static Input * getInstance();

    void setMousePoint(float x,float y);
    Vector2 getMousePoint();


};
