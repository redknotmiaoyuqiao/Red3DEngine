#pragma once

#include "GL/RedGL.hpp"
#include "Engine/RedScript.hpp"

class RedGame
{
public:
    RedScript * redScript;

    RedGame()
    {
        redScript = new RedScript();
    }

    void Start()
    {
        //背面剔除
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glFrontFace(GL_CCW);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        //深度测试
        glEnable(GL_DEPTH_TEST);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

        redScript->Start();
    }

    void Update()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Screen * screen = Screen::getInstance();
        glViewport(0,0,screen->getWidth(),screen->getHeight());

        redScript->Update();
    }

    void End()
    {
        redScript->End();
    }
};
