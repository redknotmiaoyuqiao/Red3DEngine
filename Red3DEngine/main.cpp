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
#include "Engine/RedGame.hpp"

#include "Engine/RedScript.hpp"

GLFWwindow* window;

//int width = 1280;
//int height = 720;

int width = 2560;
int height = 1600;

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

    ScreenWidth = 2560;
    ScreenHeight = 1600;

    window = glfwCreateWindow( width, height, "Red3DEngine", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_DECORATED, GL_FALSE);

    // Set the required callback functions
    glfwSetKeyCallback(window, RedScript::key_callback);
    glfwSetCursorPosCallback(window, RedScript::mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    glfwSetCursorPos(window,width/2.0f,height/2.0f);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    //glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    //Screen::width = width;
    //Screen::height = height;

    ScreenWidth = width;
    ScreenHeight = height;

    RedGame * redgame = new RedGame();
    redgame->Start();

    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 )
    {
        redgame->Update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    redgame->End();
    delete redgame;

    glfwTerminate();

    return 0;
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(yoffset);
}

