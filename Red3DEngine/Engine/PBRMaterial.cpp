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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->albedoMap->TextureId);
    glUniform1i(program->GetUniformLocation("albedoMap"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->metallicMap->TextureId);
    glUniform1i(program->GetUniformLocation("metallicMap"), 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, this->roughnessMap->TextureId);
    glUniform1i(program->GetUniformLocation("roughnessMap"), 2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, this->normalMap->TextureId);
    glUniform1i(program->GetUniformLocation("normalMap"), 3);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, this->aoMap->TextureId);
    glUniform1i(program->GetUniformLocation("aoMap"), 4);
}
