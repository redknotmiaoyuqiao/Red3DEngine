#include "GL/RedGL.hpp"
#include "GL/File.hpp"

GLCubeMapTexture::GLCubeMapTexture()
{
    glGenTextures(1,&TextureId);
}

GLCubeMapTexture::~GLCubeMapTexture()
{

}

void GLCubeMapTexture::LoadImage(vector<std::string> * faces)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, TextureId);

    int width, height;
    for (unsigned int i = 0; i < faces->size(); i++)
    {
        ImageFile * imageFile = new ImageFile();
        unsigned char * data = imageFile->ReadImage((char *)(*faces)[i].c_str(), &width, &height);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        delete imageFile;
        free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
