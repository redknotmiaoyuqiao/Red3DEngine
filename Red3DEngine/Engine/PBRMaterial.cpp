#include <Engine/Engine.hpp>

PBRMaterial::PBRMaterial()
{
    this->albedoMap = NULL;
    this->metallicMap = NULL;
    this->roughnessMap = NULL;
    this->normalMap = NULL;
    this->aoMap = NULL;
}

PBRMaterial::~PBRMaterial()
{
    if(this->albedoMap != NULL){
        delete this->albedoMap;
    }
    if(this->metallicMap != NULL){
        delete this->metallicMap;
    }
    if(this->roughnessMap != NULL){
        delete this->roughnessMap;
    }
    if(this->normalMap != NULL){
        delete this->normalMap;
    }
    if(this->aoMap != NULL){
        delete this->aoMap;
    }
}

void PBRMaterial::setAlbedoMap(GLTexture * albedoMap)
{
    this->albedoMap = albedoMap;
}

void PBRMaterial::setMetallicMap(GLTexture * metallicMap)
{
    this->metallicMap = metallicMap;
}

void PBRMaterial::setRoughnessMap(GLTexture * roughnessMap)
{
    this->roughnessMap = roughnessMap;
}

void PBRMaterial::setNormalMap(GLTexture * normalMap)
{
    this->normalMap = normalMap;
}

void PBRMaterial::setAoMap(GLTexture * aoMap)
{
    this->aoMap = aoMap;
}

void PBRMaterial::UseMaterial(GLProgram * program)
{
    program->UseProgram();

    if(this->albedoMap != NULL){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->albedoMap->TextureId);
        glUniform1i(program->GetUniformLocation("albedoMap"), 0);
    }
    if(this->metallicMap != NULL){
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->metallicMap->TextureId);
        glUniform1i(program->GetUniformLocation("metallicMap"), 1);
    }
    if(this->roughnessMap != NULL){
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, this->roughnessMap->TextureId);
        glUniform1i(program->GetUniformLocation("roughnessMap"), 2);
    }
    if(this->normalMap != NULL){
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, this->normalMap->TextureId);
        glUniform1i(program->GetUniformLocation("normalMap"), 3);
    }
    if(this->aoMap != NULL){
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, this->aoMap->TextureId);
        glUniform1i(program->GetUniformLocation("aoMap"), 4);
    }
}
