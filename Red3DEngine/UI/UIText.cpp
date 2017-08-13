#include <UI/UI.hpp>

#include "Engine/Engine.hpp"
#include "SHADER/Shader.hpp"

UIText::UIText()
{
    characterList = new std::vector<UICharacter *>();
}

UIText::UIText(char * text,int size,float x,float y)
{
    characterList = new std::vector<UICharacter *>();
    this->text = text;
    this->size = size;
    this->startX = x;
    this->startY = y;

    GLShader * text_v_shader = new GLShader(GL_VERTEX_SHADER,TEXT_VERTEX);
    GLShader * text_f_shader = new GLShader(GL_FRAGMENT_SHADER,TEXT_FRAGMENT);
    text_program = new GLProgram();
    text_program->AddShader(text_v_shader);
    text_program->AddShader(text_f_shader);
    text_program->LinkProgram();

    float char_start_x = x;
    float char_start_y = y;

    int i=0;
    while(true){
        char c = text[i];
        if(c == '\0'){
            break;
        }

        UICharacter * uiCharacter = new UICharacter(text_program,c,size,&char_start_x,&char_start_y);
        characterList->push_back(uiCharacter);

        i++;
    }
}

UIText::~UIText()
{

}

void UIText::setSize(int size)
{

}

void UIText::setPosition(float x,float y)
{

}

void UIText::Draw()
{
    int count = characterList->size();
    for(int i=0;i<count;i++){
        (*characterList)[i]->Draw();
    }
}
