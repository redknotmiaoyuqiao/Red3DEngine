#include "Engine.hpp"
#include "RedGL/RedGL.hpp"
#include "DEBUG/Debug.hpp"
#include "SHADER/Shader.hpp"
#include "Component/Component.hpp"
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


GLuint framebuffer;
GLuint texColorBuffer;

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


    glViewport(0,0,screen->getWidth(),screen->getHeight());
    //FBO
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Generate texture
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen->getWidth(), screen->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screen->getWidth(), screen->getHeight());
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


float w = 0.0f;

void Engine::Update()
{
    Screen * screen = Screen::getInstance();
    glViewport(0,0,screen->getWidth(),screen->getHeight());

    mainCamera->setCameraWidthHeight(screen->getWidth(),screen->getHeight());



    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
    glEnable(GL_DEPTH_TEST);

    glm::mat4 model;
    model = glm::scale(model,glm::vec3(1.0f));
    model = glm::rotate(model,glm::radians(w),glm::vec3(0.0f,1.0f,0.0f));
    w = w + 0.5f;
    g->putMatrix4fv("model",glm::value_ptr(model));
    g->putMatrix4fv("projection",glm::value_ptr(mainCamera->getProjection()));
    g->putMatrix4fv("view",glm::value_ptr(mainCamera->getView()));

    g->UseProgram();
    vao->DrawVAO();








    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    s->UseProgram();
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    vao_s->DrawVAO();


    /*
    screenShader.Use();
    glBindVertexArray(quadVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    */
}

void Engine::End()
{
    delete g;
    delete vao;
    delete mainCamera;
}
