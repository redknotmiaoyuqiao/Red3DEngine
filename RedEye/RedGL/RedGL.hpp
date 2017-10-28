#include <GL/glew.h>
#include <vector>

class GLShader
{
private:
public:
    GLuint ShaderId;

    GLShader(GLenum type, const GLchar* src);
    ~GLShader();
    void DeleteShader();
};

class GLProgram
{
private:
public:
    GLuint ProgramId;
    std::vector<GLShader *> ShaderList;

    GLProgram();
    ~GLProgram();
    GLProgram(const char * vertexShaderSrc,const char * fragmentShaderSrc);

    void AddShader(GLShader * shader);
    void LinkProgram();
    void UseProgram();

    GLuint GetUniformLocation(char * name);

    void putMatrix4fv(char * name,const GLfloat* value);
};


class GLVAO
{
private:
public:
    GLuint VAOId;

    GLuint EBOId;

    std::vector<GLuint> VBOList;

    int DrawTime;

    GLVAO();
    ~GLVAO();
    void SetEBO(GLuint * EBOdata,int bufferSize);
    void AddVBO(GLfloat * VBOdata,int bufferSize,int layout,int size = 3);
    void DrawVAO();
    void DeleteVAO();
};


#define RED_TARGET_TEXTURE 0
#define RED_TARGET_SCREEN 1

class GLRenderTarget{
private:
    GLuint framebuffer;
    GLuint texColorBuffer;
    GLuint rbo;

    int target;
public:
    GLRenderTarget(int width,int height,int target);
    ~GLRenderTarget();

    void setWidthAndHeight(int width,int height);

    void useFrameBuffer();

    GLuint getTextureId();
};
