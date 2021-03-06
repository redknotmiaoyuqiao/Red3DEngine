#pragma once

#include "DEBUG/Debug.hpp"
#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <vector>
#include "stdio.h"

class GLShader
{
private:
public:
    GLuint ShaderId;

    GLShader(GLenum type, const GLchar* src);
    void DeleteShader();
};

class GLProgram
{
private:
public:
    GLuint ProgramId;
    std::vector<GLShader *> ShaderList;

    GLProgram();
    void AddShader(GLShader * shader);
    void LinkProgram();
    void UseProgram();

    GLuint GetUniformLocation(char * name);
};

class GLTexture
{
private:
public:
    GLuint TextureId;

    GLTexture();
    ~GLTexture();
    void LoadImage(char * filePath);
    void SetData(unsigned char * data,int width,int height,GLenum internalFormat,GLenum format);
    void SetCharData(unsigned char * data,int width,int height);
};

class GLVAO
{
private:
public:
    GLuint VAOId;\

    GLuint EBOId;
    std::vector<GLuint> VBOList;
    int DrawTime;

    GLVAO();
    ~GLVAO();
    void SetEBO(GLuint * EBOdata,int bufferSize);
    void AddVBO(GLfloat * VBOdata,int bufferSize,int layout,int size);
    void DrawVAO();
    void DeleteVAO();
};

class GLCubeMapTexture
{
private:
public:
    GLuint TextureId;

    GLCubeMapTexture();
    ~GLCubeMapTexture();

    void LoadImage(vector<std::string> * faces);
};
