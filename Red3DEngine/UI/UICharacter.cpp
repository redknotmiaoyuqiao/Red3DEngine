#include "UI/UI.hpp"
#include "Engine/Engine.hpp"
#include <GL/glew.h>

UICharacter::UICharacter(GLProgram * program,char c,int size,float * x,float * y)
{
    this->program = program;
    this->c = c;
    this->size = size;
    this->startX = *x;
    this->startY = *y;

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, "/Users/redknot/Red3DEngine/Font/EnglischeSchTDemBol.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, size);

    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

    Screen * screen = Screen::getInstance();

    float w = face->glyph->bitmap.width / ((float)screen->getWidth());
    float h = face->glyph->bitmap.rows / ((float)screen->getHeight());
    float top = face->glyph->bitmap_top / ((float)screen->getHeight());
    float advance = face->glyph->advance.x / ((float)screen->getWidth() * 64 * 8);

    *x = this->startX + w + 0.0f;

    RedLog("W:%f\n",w);
    RedLog("H:%f\n",h);

    RedLog("\n\n\n");

    float com_x = startX;
    float com_y = startY + top - size/((float)2200);

    GLfloat textArr[] = {
        com_x,com_y,0.0f,
        com_x + w, com_y, 0.0f,
        com_x + w, com_y - h,0.0f,
        com_x,com_y - h,0.0f
    };

    GLfloat textCoor[] = {
        0.0,1.0,0.0,
        1.0,1.0,0.0,
        1.0,0.0,0.0,
        0.0,0.0,0.0
    };

    unsigned int textIndex[] = {
        3,1,0,
        3,2,1
    };

    this->vao = new GLVAO();
    vao->AddVBO(textArr,sizeof(textArr),0,3);
    vao->AddVBO(textCoor,sizeof(textCoor),1,3);
    vao->SetEBO(textIndex,sizeof(textIndex));

    this->texture = new GLTexture();
    texture->SetCharData(face->glyph->bitmap.buffer,face->glyph->bitmap.width,face->glyph->bitmap.rows);
}

UICharacter::~UICharacter()
{
    delete this->texture;
    delete this->vao;
}

void UICharacter::Draw()
{
    this->program->UseProgram();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->TextureId);
    glUniform1i(program->GetUniformLocation("text_texture"), 0);

    glUniform3f(program->GetUniformLocation("text_color"),1.0,0.0,0.0);

    this->vao->DrawVAO();
}
