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

GLFWwindow* window;

int width = 700;
int height = 700;


glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

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
    //glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
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


    GLfloat vertices[] = {
        1.0f,0.0f,1.0f,
        1.0f,0.0f,-1.0f,
        -1.0f,0.0f,-1.0f,
        -1.0f,0.0f,1.0f,
        1.0f,2.0f,1.0f,
        1.0f,2.0f,-1.0f,
        -1.0f,2.0f,-1.0f,
        -1.0f,2.0f,1.0f
    };

    GLuint indices[] = { // 注意索引从0开始!
                         0,7,4,
                         0,3,7,

                         0,4,1,
                         1,4,5,

                         1,5,2,
                         5,6,2,

                         6,7,2,
                         7,3,2,

                         4,7,6,
                         4,6,5,

                         0,2,3,
                         0,1,2
    };

    GLfloat txtcoor[] = {
        1.0f, 1.0, 0.0f,   // 右上角
        1.0f, 0.0f, 0.0f,  // 右下角
        0.0f, 0.0f, 0.0f, // 左下角
        0.0f, 1.0f, 0.0f   // 左上角
    };

    GLfloat normal[] = {
        1.0f,-1.0f,1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,1.0f,
        1.0f,1.0f,1.0f,
        1.0f,1.0f,-1.0f,
        -1.0f,1.0f,-1.0f,
        -1.0f,1.0f,-1.0f
    };

    GLVAO * vao = new GLVAO();
    vao->AddVBO(vertices,sizeof(vertices),0,3);
    vao->AddVBO(normal,sizeof(normal),1,3);
    vao->AddVBO(txtcoor,sizeof(txtcoor),2,3);
    vao->SetEBO(indices,sizeof(indices));

    GLTexture * image = new GLTexture();
    image->LoadImage("/Users/redknot/Desktop/huaji.jpg");

    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model;
        model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(30.0f), width / (height * 1.0f), 0.1f, 100.0f);

        program->UseProgram();

        glUniformMatrix4fv(program->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(program->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(program->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glUniform3f(program->GetUniformLocation("objectColor"), 1.0f, 0.5f, 0.31f);// 我们所熟悉的珊瑚红
        glUniform3f(program->GetUniformLocation("lightColor"),  1.0f, 1.0f, 1.0f); // 依旧把光源设置为白色

        glUniform3f(program->GetUniformLocation("lightPos"),  3.0f, 5.0f, 3.0f);
        glUniform3f(program->GetUniformLocation("viewPos"),  cameraPos[0],cameraPos[1],cameraPos[2]);

        glActiveTexture(GL_TEXTURE0); //在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, image->TextureId);
        glUniform1i(program->GetUniformLocation("image"), 0);

        vao->DrawVAO();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glDeleteBuffers(1, &vertexbuffer);
    //glDeleteVertexArrays(1, &VertexArrayID);
    //glDeleteProgram(programID);

    delete v_shader;
    delete f_shader;
    delete program;
    delete vao;

    delete image;

    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    GLfloat cameraSpeed = 0.05f;
    if(key == GLFW_KEY_W)
        cameraPos += cameraSpeed * cameraFront;
    if(key == GLFW_KEY_S)
        cameraPos -= cameraSpeed * cameraFront;
    if(key == GLFW_KEY_A)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(key == GLFW_KEY_D)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(yoffset);
}

