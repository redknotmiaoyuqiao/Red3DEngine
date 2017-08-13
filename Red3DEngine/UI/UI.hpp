#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <vector>
#include "GL/RedGL.hpp"

class UICharacter{
private:
    char c;
    int size = 50;

    float startX;
    float startY;

    GLVAO * vao;
    GLTexture * texture;
    GLProgram * program;
public:
    UICharacter(GLProgram * program,char c,int size,float * x,float * y);
    ~UICharacter();

    void Draw();
};

class UIText
{
private:
    char * text;
    float startX = 0.0f;
    float startY = 0.0f;

    int size = 50;

    std::vector<UICharacter *> * characterList;

    GLProgram * text_program;
public:
    UIText();
    UIText(char * text,int size,float x = 0.0f,float y = 0.0f);

    ~UIText();

    void setSize(int size);
    void setPosition(float x,float y);
    void Draw();
};


