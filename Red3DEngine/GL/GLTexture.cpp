#include "RedGL.hpp"

#include "GL/File.hpp"

#ifdef __ANDROID__

#else
#include <SOIL/SOIL.h>
#endif


GLTexture::GLTexture()
{
    glGenTextures(1, &TextureId);
    glBindTexture(GL_TEXTURE_2D, TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture::~GLTexture()
{
    //glDeleteTextures(TextureId);
}

void GLTexture::LoadImage(char * filePath)
{
    glBindTexture(GL_TEXTURE_2D, TextureId);

    #ifdef __ANDROID__
    int width, height;

    ImageFile * readImage = new ImageFile();
    unsigned char* image = readImage->ReadImage(filePath,&width,&height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    RedLog("-------------LoadImage Start-------------\n");
    RedLog("Path:%s\n",filePath);
    RedLog("width:%d\nheight:%d\n",width,height);
    RedLog("-------------LoadImage End---------------\n\n\n\n");

    #else
    int width, height;
    unsigned char * image = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    RedLog("-------------LoadImage Start-------------\n");
    RedLog("Path:%s\n",filePath);
    RedLog("width:%d\nheight:%d\n",width,height);
    RedLog("-------------LoadImage End---------------\n\n\n\n");

    SOIL_free_image_data(image);
    #endif

    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture::SetData(unsigned char * data,int width,int height,GLenum internalFormat,GLenum format)
{
    glBindTexture(GL_TEXTURE_2D, TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}
