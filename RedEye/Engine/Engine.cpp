#include "Engine.hpp"
#include "RedGL/RedGL.hpp"
#include "DEBUG/Debug.hpp"
#include "SHADER/Shader.hpp"
#include <GL/glew.h>

float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
};


GLVAO * vao;
GLProgram * g;

void Engine::Start()
{
    RedLog("Engine Start !!!!");
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    g = new GLProgram(test_VERTEX,test_FRAGMENT);

    vao = new GLVAO();
    vao->AddVBO(vertices,sizeof(vertices),0);
    vao->SetEBO(indices,sizeof(indices));
}


void Engine::Update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    g->UseProgram();
    vao->DrawVAO();
}

void Engine::End()
{
    delete g;
    delete vao;
}
