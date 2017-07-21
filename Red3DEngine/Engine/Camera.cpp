#include "Engine/Engine.hpp"

Camera::Camera(float fovy,float width,float height,float near,float far)
{
    cameraPos = new float[3];
    cameraFront = new float[3];
    cameraUp = new float[3];

    this->width = width;
    this->height = height;
    this->fovy = fovy;
    this->near = near;
    this->far = far;
}

Camera::~Camera()
{
    delete cameraPos;
    delete cameraFront;
    delete cameraUp;
}

void Camera::setCameraPos(float x,float y,float z)
{
    cameraPos[0] = x;
    cameraPos[1] = y;
    cameraPos[2] = z;
}

void Camera::setCameraFront(float x,float y,float z)
{
    cameraFront[0] = x;
    cameraFront[1] = y;
    cameraFront[2] = z;
}

void Camera::setCameraUp(float x,float y,float z)
{
    cameraUp[0] = x;
    cameraUp[1] = y;
    cameraUp[2] = z;
}

void Camera::UseCamera(GLProgram * program)
{
    glm::vec3 v_cameraPos   = glm::vec3(cameraPos[0], cameraPos[1],  cameraPos[2]);
    glm::vec3 v_cameraFront = glm::vec3(cameraFront[0], cameraFront[1], cameraFront[2]);
    glm::vec3 v_cameraUp    = glm::vec3(cameraUp[0], cameraUp[1],  cameraUp[2]);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(this->fovy), width / (height * 1.0f), near, far);

    glUniformMatrix4fv(program->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 view;
    view = glm::lookAt(v_cameraPos, v_cameraPos + v_cameraFront, v_cameraUp);
    glUniformMatrix4fv(program->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));

    glUniform3f(program->GetUniformLocation("viewPos"),  v_cameraPos[0],v_cameraPos[1],v_cameraPos[2]);
}
