#include "RedGL.hpp"
#include <GL/glew.h>
#include "GL/File.hpp"

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

    int width, height;

    ImageFile * imageFile = new ImageFile();
    unsigned char * image = imageFile->ReadImage(filePath,&width,&height);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);

    delete imageFile;
    free(image);
}

void GLTexture::SetData(unsigned char * data,int width,int height,GLenum internalFormat,GLenum format)
{
    glBindTexture(GL_TEXTURE_2D, TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}
