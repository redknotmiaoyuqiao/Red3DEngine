#include "RedGL.hpp"
#include "DEBUG/Debug.hpp"

GLProgram::GLProgram()
{
    ProgramId = glCreateProgram();
}

GLProgram::~GLProgram(){
    int size = ShaderList.size();
    for(int i=0;i<size;i++){
        glDetachShader(ProgramId, ShaderList[i]->ShaderId);
        delete ShaderList[i];
    }

    ShaderList.clear();
}

GLProgram::GLProgram(const char * vertexShaderSrc,const char * fragmentShaderSrc)
{
    ProgramId = glCreateProgram();

    GLShader * v_shader = new GLShader(GL_VERTEX_SHADER,vertexShaderSrc);
    GLShader * f_shader = new GLShader(GL_FRAGMENT_SHADER,fragmentShaderSrc);
    this->AddShader(v_shader);
    this->AddShader(f_shader);
    this->LinkProgram();
}

void GLProgram::AddShader(GLShader * shader)
{
    ShaderList.push_back(shader);
}

void GLProgram::LinkProgram()
{
    int size = ShaderList.size();
    for(int i=0;i<size;i++){
        glAttachShader(ProgramId, ShaderList[i]->ShaderId);
    }

    glLinkProgram(ProgramId);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Check the program
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    for(int i=0;i<size;i++){
        glDetachShader(ProgramId, ShaderList[i]->ShaderId);
        delete ShaderList[i];
    }

    ShaderList.clear();
}

void GLProgram::UseProgram()
{
    glUseProgram(ProgramId);
}

GLuint GLProgram::GetUniformLocation(char * name)
{
    return glGetUniformLocation(ProgramId,name);
}
