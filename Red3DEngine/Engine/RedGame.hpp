#pragma once

#include "GL/RedGL.hpp"
#include "Engine/RedScript.hpp"

#include "User/MyNano.hpp"

class RedGame
{
public:

    int width;
    int height;

    RedScript * nano;

    RedGame(int width,int height)
    {
        this->width = width;
        this->height = height;

        nano = new MyNano();
    }

    void Start()
    {
        //背面剔除
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        //深度测试
        glEnable(GL_DEPTH_TEST);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        nano->Start();
    }

    void Update()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        nano->Update();
    }

    void End()
    {
        nano->End();
    }
};
