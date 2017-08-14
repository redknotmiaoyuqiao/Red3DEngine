#include "Engine/Engine.hpp"

Screen * Screen::m_pInstance = NULL;

Screen::Screen(){
    this->ScreenWidth = 0.0f;
    this->ScreenHeight = 0.0f;
}

Screen * Screen::getInstance()
{
    if(m_pInstance == NULL){
        m_pInstance = new Screen();
    }
    return m_pInstance;
}

void Screen::setWidthAndHeight(float width,float height)
{
    this->ScreenWidth = width;
    this->ScreenHeight = height;
}

float Screen::getWidth()
{
    return this->ScreenWidth;
}

float Screen::getHeight()
{
    return this->ScreenHeight;
}
