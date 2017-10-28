#include "Engine.hpp"
#include "RedGL/RedGL.hpp"
#include "DEBUG/Debug.hpp"
#include "SHADER/Shader.hpp"
#include "Component/Component.hpp"
#include "File/File.hpp"
#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

float vertices[] = {
    1.0f,1.0f,0.0f,
    1.0f,-1.0f,0.0f,
    -1.0f,-1.0f,0.0f
    };
unsigned int indices[] = {
    0,1,2
};


float vertices_s[] = {
    1.0f,1.0f,0.0f,
    1.0f,-1.0f,0.0f,
    -1.0f,-1.0f,0.0f,
    -1.0f,1.0f,0.0f
    };
float coor_s[] = {
    1.0f,1.0f,0.0f,
    1.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f
    };
unsigned int indices_s[] = {
    0,1,2,
    0,2,3
};


GLVAO * vao_s;

GLVAO * vao;
GLProgram * g;
GLProgram * s;
Camera * mainCamera;

GLRenderTarget * target;
GLRenderTarget * target_screen;


GLuint framebuffer;
GLuint texColorBuffer;
GLuint rbo;

void Engine::Start()
{
    RedLog("Engine Start !!!!");
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    g = new GLProgram(test_VERTEX,test_FRAGMENT);
    s = new GLProgram(s_VERTEX,s_FRAGMENT);

    vao = new GLVAO();
    vao->AddVBO(vertices,sizeof(vertices),0);
    vao->SetEBO(indices,sizeof(indices));


    vao_s = new GLVAO();
    vao_s->AddVBO(vertices_s,sizeof(vertices_s),0);
    vao_s->AddVBO(coor_s,sizeof(coor_s),1);
    vao_s->SetEBO(indices_s,sizeof(indices_s));



    Screen * screen = Screen::getInstance();
    mainCamera = new Camera(30.0f,screen->getWidth(),screen->getHeight(),0.1f,1000.0f);

    target = new GLRenderTarget(screen->getWidth(),screen->getHeight(),RED_TARGET_SCREEN);
    target_screen = new GLRenderTarget(screen->getWidth(),screen->getHeight(),RED_TARGET_SCREEN);
}


float w = 0.0f;

void Engine::Update()
{
    Screen * screen = Screen::getInstance();
    glViewport(0,0,screen->getWidth(),screen->getHeight());

    target->setWidthAndHeight(screen->getWidth(),screen->getHeight());
    target->useFrameBuffer();

    mainCamera->setCameraWidthHeight(screen->getWidth(),screen->getHeight());

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model;
    model = glm::scale(model,glm::vec3(1.0f));
    model = glm::rotate(model,glm::radians(w),glm::vec3(0.0f,1.0f,0.0f));
    w = w + 0.5f;
    g->putMatrix4fv("model",glm::value_ptr(model));
    g->putMatrix4fv("projection",glm::value_ptr(mainCamera->getProjection()));
    g->putMatrix4fv("view",glm::value_ptr(mainCamera->getView()));

    g->UseProgram();
    vao->DrawVAO();






    /*
    target_screen->useFrameBuffer();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    s->UseProgram();
    glBindTexture(GL_TEXTURE_2D, target->getTextureId());
    vao_s->DrawVAO();
    */
}

void Engine::End()
{
    delete g;
    delete vao;
    delete mainCamera;
}
