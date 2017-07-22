#pragma once

#include "GL/File.hpp"

class RedScript
{
public:

    GLProgram * program;
    Model * m;
    Light * light;
    Camera * mainCamera;

    void Start(){
      TextFile * readFile = new TextFile();

      char * v_shader_code = readFile->ReadFile("/Users/redknot/Red3DEngine/Red3DEngine/GLSL/v_shader.vert");
      char * f_shader_code = readFile->ReadFile("/Users/redknot/Red3DEngine/Red3DEngine/GLSL/f_shader.frag");

      //char * v_shader_code = readFile->ReadFile("/storage/emulated/0/3D/GLSL/v_shader.vert");
      //char * f_shader_code = readFile->ReadFile("/storage/emulated/0/3D/GLSL/f_shader.frag");

      delete readFile;


      //char * v_shader_code = "void main()";
      //char * f_shader_code = "void main()";

      GLShader * v_shader = new GLShader(GL_VERTEX_SHADER,v_shader_code);
      GLShader * f_shader = new GLShader(GL_FRAGMENT_SHADER,f_shader_code);

      program = new GLProgram();
      program->AddShader(v_shader);
      program->AddShader(f_shader);
      program->LinkProgram();

        std::string path = "/Users/redknot/Red3DEngine/3dModel/nano";
      //std::string path = "/storage/emulated/0/3D/nano";
      m = new Model(path);

      //light
      light = new Light();
      light->setAmbient(1.0f);
      light->setDiffuse(1.3f);
      light->setSpecular(100.3f);
      light->setPosition(800.0f);

      //Camera
      int width = 1280;
      int height = 720;

      mainCamera = new Camera(30.0f,width * 1.0f,height * 1.0f,0.1f,1000.0f);
      mainCamera->setCameraPos(0.0f, 8.0f,  40.0f);
      mainCamera->setCameraFront(0.0f, 0.0f, -1.0f);
      mainCamera->setCameraUp(0.0f, 1.0f,  0.0f);
    }

    float w = 0.0f;

    void Update(){
      w = w + 0.01f;
      mainCamera->setCamera(30.0f,ScreenWidth * 1.0f,ScreenHeight * 1.0f,0.1f,1000.0f);

      program->UseProgram();

      mainCamera->UseCamera(program);
      light->UseLight(program);

      glm::mat4 model;
      //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
      model = glm::rotate(model, glm::radians((GLfloat)w * 80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      glUniformMatrix4fv(program->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

      m->Draw(program);
    }

    void End()
    {
      delete program;
      delete mainCamera;
      delete light;
      delete m;
    }
};
