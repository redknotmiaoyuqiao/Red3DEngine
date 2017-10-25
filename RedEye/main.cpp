#include "DEBUG/Debug.hpp"
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "Engine/Engine.hpp"

int main()
{
    RedLog("Welcame RedEye!!!!\n\n");

    RedLog("Initialize GLFW\n");
    if( !glfwInit() )
    {
        RedLog("Failed to initialize GLFW\n");
        return -1;
    }
    RedLog("Initialize GLFW Success!!!\n");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //不可改变大小
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //没有边框
    //glfwWindowHint(GLFW_DECORATED, GL_FALSE);

    GLFWwindow * window;
    int width = 800;
    int height = 640;

    bool isFullScreen = false;
    GLFWmonitor* pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;

    window = glfwCreateWindow(width, height, "RedEye", pMonitor, NULL);
    if( window == NULL ){
        RedLog("Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        RedLog("Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    Engine * RedEngine = new Engine();
    RedEngine->Start();

    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 )
    {
        RedEngine->Update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    RedEngine->End();

    delete RedEngine;

    glfwTerminate();

    return 0;
}
