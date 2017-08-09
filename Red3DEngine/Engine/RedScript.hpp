#pragma once

#include <SOIL/SOIL.h>

#include "GL/File.hpp"
#include "GLFW/glfw3.h"
#include "Engine/Engine.hpp"
#include "SHADER/Shader.hpp"


#include <ft2build.h>
#include FT_FREETYPE_H



glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;

bool keys[1024];

void do_movement();

class RedScript
{
public:
    GLProgram * program;
    GLProgram * sky_program;
    Model * m;
    Camera * mainCamera;

    //四个点光源
    PBRLight * light0;
    PBRLight * light1;
    PBRLight * light2;
    PBRLight * light3;

    GLTexture * albedoMap;
    GLTexture * metallicMap;
    GLTexture * roughnessMap;
    GLTexture * normalMap;
    GLTexture * aoMap;

    PBRMaterial * pbrMaterial;

    GLVAO * sky_vao;

    SkyBox * skybox;

    void Start(){
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

        FT_Face face;
        if (FT_New_Face(ft, "/Users/redknot/Red3DEngine/Font/Arial.ttf", 0, &face))
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

        FT_Set_Pixel_Sizes(face, 0, 48);

        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

        /*
        albedoMap = new GLTexture();
        albedoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_A.png");
        metallicMap = new GLTexture();
        metallicMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_M.png");
        roughnessMap = new GLTexture();
        roughnessMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_N.png");
        normalMap = new GLTexture();
        normalMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_R.png");
        aoMap = new GLTexture();
        aoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_AO.png");

        pbrMaterial = new PBRMaterial();
        pbrMaterial->setAlbedoMap(albedoMap);
        pbrMaterial->setMetallicMap(metallicMap);
        pbrMaterial->setNormalMap(normalMap);
        pbrMaterial->setRoughnessMap(roughnessMap);
        pbrMaterial->setAoMap(aoMap);
        */

        pbrMaterial = new PBRMaterial();



        GLShader * sky_v_shader = new GLShader(GL_VERTEX_SHADER,SKY_VERTEX);
        GLShader * sky_f_shader = new GLShader(GL_FRAGMENT_SHADER,SKY_FRAGMENT);

        sky_program = new GLProgram();
        sky_program->AddShader(sky_v_shader);
        sky_program->AddShader(sky_f_shader);
        sky_program->LinkProgram();



        GLShader * v_shader = new GLShader(GL_VERTEX_SHADER,PBR_VERTEX);
        GLShader * f_shader = new GLShader(GL_FRAGMENT_SHADER,PBR_FRAGMENT);

        program = new GLProgram();
        program->AddShader(v_shader);
        program->AddShader(f_shader);
        program->LinkProgram();

#ifdef __ANDROID__
        std::string path = "/storage/emulated/0/3D/nano";
        //std::string path = "/data/data/com.redknot.red3dengineandroid/cache/nano";
#else
        //std::string path = "/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/Cerberus_LP";
        std::string path = "/Users/redknot/Red3DEngine/3dModel/qiu";
#endif

        m = new Model(path);

        //light
        light0 = new PBRLight();
        light0->setColor(300.0f,300.0f,300.0f);
        light0->setPosition(-10.0f,  10.0f, 10.0f);

        light1 = new PBRLight();
        light1->setColor(300.0f,300.0f,300.0f);
        light1->setPosition(10.0f,  10.0f, 10.0f);

        light2 = new PBRLight();
        light2->setColor(300.0f,300.0f,300.0f);
        light2->setPosition(-10.0f, -10.0f, 10.0);

        light3 = new PBRLight();
        light3->setColor(300.0f,300.0f,300.0f);
        light3->setPosition(10.0f, -10.0f, 10.0f);


        //Camera
        int width = 1280;
        int height = 720;

        cameraPos.x = 0.0f;
        cameraPos.y = 0.0f;
        cameraPos.z = 30.0f;

        cameraFront.x = 0.0f;
        cameraFront.y = 0.0f;
        cameraFront.z = -1.0f;

        cameraUp.x = 0.0f;
        cameraUp.y = 1.0f;
        cameraUp.z = 0.0f;

        mainCamera = new Camera(30.0f,width * 1.0f,height * 1.0f,0.1f,1000.0f);

        //绘制天空盒子
        vector<std::string> faces =
        {
            "/Users/redknot/Red3DEngine/Texture/SkyBox/right.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/left.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/top.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/bottom.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/back.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/front.jpg"
        };
        skybox = new SkyBox();
        skybox->loadTexture(&faces);
    }

    float w = 0.0f;

    void Update(){

        do_movement();

        mainCamera->setCameraPos(cameraPos.x,cameraPos.y,cameraPos.z);
        mainCamera->setCameraFront(cameraFront.x,cameraFront.y,cameraFront.z);
        mainCamera->setCameraUp(cameraUp.x,cameraUp.y,cameraUp.z);

        sky_program->UseProgram();
        skybox->UseSkyBox(sky_program,mainCamera);


        program->UseProgram();
        pbrMaterial->UseMaterial(program);

        //更新相机位置
        mainCamera->UseCamera(program);

        //更新灯光
        light0->UseLight(program,0);
        light1->UseLight(program,1);
        light2->UseLight(program,2);
        light3->UseLight(program,3);

        //更新模型位置
        glm::mat4 model;
        //model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
        //model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        glUniformMatrix4fv(program->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
        m->Draw(program);

    }

    void End()
    {
        delete program;
        delete sky_program;
        delete mainCamera;
        delete m;

        delete light0;
        delete light1;
        delete light2;
        delete light3;
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};

GLfloat yaw   = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch =   0.0f;
GLfloat lastX =  ScreenWidth  / 2.0;
GLfloat lastY =  ScreenHeight / 2.0;
bool firstMouse = true;

void RedScript::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    //RedLog("xpos:%f\n",xpos);
    //RedLog("ypos:%f\n",ypos);
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

    GLfloat sensitivity = 0.3f;
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
    cameraFront = glm::normalize(front);
}

void RedScript::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement()
{
    // Camera controls
    GLfloat cameraSpeed = 0.07f;
    if (keys[GLFW_KEY_W])
        cameraPos += cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_S])
        cameraPos -= cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_A])
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


