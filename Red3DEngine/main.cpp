#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GL/RedGL.hpp"
#include "GL/File.hpp"

#include "Engine/Engine.hpp"

GLFWwindow* window;

int width = 1280;
int height = 720;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main( void )
{
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    //glfwWindowHint(GLFW_DECORATED, GL_FALSE);

    window = glfwCreateWindow( width, height, "Red3DEngine", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    //背面剔除
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //深度测试
    glEnable(GL_DEPTH_TEST);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    TextFile * readFile = new TextFile();
    char * v_shader_code = readFile->ReadFile("/Users/redknot/Red3DEngine/Red3DEngine/GLSL/v_shader.vert");
    char * f_shader_code = readFile->ReadFile("/Users/redknot/Red3DEngine/Red3DEngine/GLSL/f_shader.frag");
    delete readFile;

    GLShader * v_shader = new GLShader(GL_VERTEX_SHADER,v_shader_code);
    GLShader * f_shader = new GLShader(GL_FRAGMENT_SHADER,f_shader_code);

    GLProgram * program = new GLProgram();
    program->AddShader(v_shader);
    program->AddShader(f_shader);
    program->LinkProgram();

    //std::string path = "/Users/redknot/Desktop/nanosuit/nanosuit.obj";
    //std::string path = "/Users/redknot/Desktop/Face2.FBX";

    //std::string path = "/Users/redknot/Desktop/Cubeq/Cube.FBX";
    std::string path = "/Users/redknot/Desktop/nano";
    Model * m = new Model(path);

    //light
    Light * light = new Light();
    light->setAmbient(1.0f);
    light->setDiffuse(0.9f);
    light->setSpecular(1.0f);
    light->setPosition(800.0f);

    //Camera
    Camera * mainCamera = new Camera(30.0f,width * 1.0f,height * 1.0f,0.1f,1000.0f);
    mainCamera->setCameraPos(0.0f, 8.0f,  40.0f);
    mainCamera->setCameraFront(0.0f, 0.0f, -1.0f);
    mainCamera->setCameraUp(0.0f, 1.0f,  0.0f);

    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program->UseProgram();

        mainCamera->UseCamera(program);
        light->UseLight(program);

        glm::mat4 model;
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(program->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

        m->Draw(program);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glDeleteBuffers(1, &vertexbuffer);
    //glDeleteVertexArrays(1, &VertexArrayID);
    //glDeleteProgram(programID);

    delete mainCamera;

    delete v_shader;
    delete f_shader;
    delete program;

    delete m;

    delete light;


    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    /*
    GLfloat cameraSpeed = 0.3f;
    if(key == GLFW_KEY_W)
        cameraPos += cameraSpeed * cameraFront;
    if(key == GLFW_KEY_S)
        cameraPos -= cameraSpeed * cameraFront;
    if(key == GLFW_KEY_A)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(key == GLFW_KEY_D)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        */
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(yoffset);
}

