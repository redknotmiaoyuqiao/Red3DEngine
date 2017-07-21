#include "Engine/Engine.hpp"

Material::Material()
{
    this->ambient = NULL;
    this->specular = NULL;
    this->normalMap = NULL;

    this->shininess = 80.0f;
}

Material::~Material()
{
    if(this->ambient != NULL){
        delete this->ambient;
    }
    if(this->specular != NULL){
        delete this->specular;
    }
    if(this->normalMap != NULL){
        delete this->normalMap;
    }
}

void Material::setAmbient(GLTexture * ambient)
{
    this->ambient = ambient;
}

void Material::setSpecular(GLTexture * specular)
{
    this->specular = specular;
}

void Material::setNormalMap(GLTexture * normalMap)
{
    this->normalMap = normalMap;
}

void Material::setShininess(float shininess)
{
    this->shininess = shininess;
}

void Material::UseMaterial(GLProgram * program)
{
    if(this->ambient != NULL){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->ambient->TextureId);
        glUniform1i(program->GetUniformLocation("material.ambient"), 0);
    }else{
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUniform1i(program->GetUniformLocation("material.ambient"), 0);
    }

    if(this->specular != NULL){
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->specular->TextureId);
        glUniform1i(program->GetUniformLocation("material.specular"), 1);
    }else{
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUniform1i(program->GetUniformLocation("material.specular"), 1);
    }

    if(this->normalMap != NULL){
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, this->normalMap->TextureId);
        glUniform1i(program->GetUniformLocation("material.normalMap"), 2);
    }else{
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUniform1i(program->GetUniformLocation("material.normalMap"), 2);
    }

    glUniform1f(program->GetUniformLocation("material.shininess"), this->shininess);
}
