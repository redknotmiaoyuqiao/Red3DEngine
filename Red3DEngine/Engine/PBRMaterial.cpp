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

void PBRMaterial::UseMaterial()
{

}
