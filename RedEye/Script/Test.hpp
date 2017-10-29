#pragma once

#include "Engine/Engine.hpp"
#include "Component/Component.hpp"
#include "DEBUG/Debug.hpp"
#include "RedGL/RedGL.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <GL/glew.h>


float vertices[] = {
    1.0f,1.0f,0.0f,
    1.0f,-1.0f,0.0f,
    -1.0f,-1.0f,0.0f,
    -1.0f,1.0f,0.0f
    };
float coor[] = {
    1.0f,1.0f,0.0f,
    1.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f
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


class Test : public RedEyeBehaviour{
private:
    GLProgram * g;
    GLProgram * s;
    GLProgram * pbr;

    GLVAO * vao_s;
    GLVAO * vao;

    Camera * mainCamera;

    GLRenderTarget * target;
    GLRenderTarget * target_s;
    GLRenderTarget * target_screen;
public:
    void Start()
    {
        glClearColor(1.0f,1.0f,1.0f,1.0f);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        g = new GLProgram(test_VERTEX,test_FRAGMENT);
        s = new GLProgram(s_VERTEX,s_FRAGMENT);
        pbr = new GLProgram(PBR_VERTEX,PBR_FRAGMENT);

        vao = new GLVAO();
        vao->AddVBO(vertices,sizeof(vertices),0);
        vao->AddVBO(coor,sizeof(coor),1);
        vao->SetEBO(indices,sizeof(indices));

        vao_s = new GLVAO();
        vao_s->AddVBO(vertices_s,sizeof(vertices_s),0);
        vao_s->AddVBO(coor_s,sizeof(coor_s),1);
        vao_s->SetEBO(indices_s,sizeof(indices_s));

        Screen * screen = Screen::getInstance();
        mainCamera = new Camera(30.0f,screen->getWidth(),screen->getHeight(),0.1f,1000.0f);

        target = new GLRenderTarget(screen->getWidth(),screen->getHeight(),RED_TARGET_SCREEN);
        target_s = new GLRenderTarget(screen->getWidth(),screen->getHeight(),RED_TARGET_TEXTURE);
        target_screen = new GLRenderTarget(screen->getWidth(),screen->getHeight(),RED_TARGET_SCREEN);

        Model * model = new Model("/Users/redknot/Red3DEngine/3dModel/Tea/tea.redmeshs");
    }

    float w = 0.0f;
    void Update()
    {
        //this->Mouse();
        //this->CameraKey();

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
        pbr->putMatrix4fv("model",glm::value_ptr(model));
        pbr->putMatrix4fv("projection",glm::value_ptr(mainCamera->getProjection()));
        pbr->putMatrix4fv("view",glm::value_ptr(mainCamera->getView()));
        pbr->UseProgram();
        vao->DrawVAO();

        /*
        target_s->setWidthAndHeight(screen->getWidth(),screen->getHeight());
        target_s->useFrameBuffer();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        s->UseProgram();
        glBindTexture(GL_TEXTURE_2D, target->getTextureId());
        vao_s->DrawVAO();


        target_screen->setWidthAndHeight(screen->getWidth(),screen->getHeight());
        target_screen->useFrameBuffer();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        s->UseProgram();
        glBindTexture(GL_TEXTURE_2D, target_s->getTextureId());
        vao_s->DrawVAO();
        */

    }

    void End()
    {
        RedLog("End");
        delete g;
        delete vao;
        delete mainCamera;

        delete target;
        delete target_screen;
    }


private:
    bool firstMouse = true;
    float lastX = 0.0f;
    float lastY = 0.0f;
    float yaw;
    float pitch;
    void Mouse()
    {
        Input * input = Input::getInstance();

        float xpos = input->getMousePoint().x;
        float ypos = input->getMousePoint().y;

        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        GLfloat sensitivity = 0.5f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);

        this->mainCamera->setCameraFront(front.x,front.y,front.z);
    }


    void CameraKey()
    {
        Input * input = Input::getInstance();

        /*
        float cameraSpeed = 0.07f;
        if (input->keys[GLFW_KEY_W])
            mainCamera->cameraPos += cameraSpeed * mainCamera->cameraFront;
        if (input->keys[GLFW_KEY_S])
            mainCamera->cameraPos -= cameraSpeed * mainCamera->cameraFront;
        if (input->keys[GLFW_KEY_A])
            mainCamera->cameraPos -= glm::normalize(glm::cross(mainCamera->cameraFront, mainCamera->cameraUp)) * cameraSpeed;
        if (input->keys[GLFW_KEY_D])
            mainCamera->cameraPos += glm::normalize(glm::cross(mainCamera->cameraFront, mainCamera->cameraUp)) * cameraSpeed;
        */
    }

};
