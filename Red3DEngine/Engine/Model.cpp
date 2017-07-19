#include "Engine.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(std::string path)
{
    meshs = new std::vector<Mesh*>();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return;
    }

    for(int i=0;i<scene->mNumMeshes;i++){
        aiMesh * paiMesh = scene->mMeshes[i];

        //将会被Mesh的析构函数释放
        std::vector<Vertex*> * vertices = new std::vector<Vertex*>();
        std::vector<GLuint> * indices = new std::vector<GLuint>();
        std::vector<Texture*> * textures = new std::vector<Texture*>();

        //paiMesh->mTangents
        //设置Vertex
        for(int j=0;j<paiMesh->mNumVertices;j++){
            Vertex * v = new Vertex;
            v->Position_x = paiMesh->mVertices[j].x;
            v->Position_y = paiMesh->mVertices[j].y;
            v->Position_z = paiMesh->mVertices[j].z;

            v->Normal_x = paiMesh->mNormals[j].x;
            v->Normal_y = paiMesh->mNormals[j].y;
            v->Normal_z = paiMesh->mNormals[j].z;

            v->TexCoords_x = paiMesh->mTextureCoords[0][j].x;
            v->TexCoords_y = paiMesh->mTextureCoords[0][j].y;

            vertices->push_back(v);
        }

        for (int j = 0 ; j < paiMesh->mNumFaces ; j++) {
            aiFace Face = paiMesh->mFaces[j];
            if(Face.mNumIndices != 3){
                continue;
            }
            indices->push_back(Face.mIndices[0]);
            indices->push_back(Face.mIndices[1]);
            indices->push_back(Face.mIndices[2]);
        }

        Mesh * mesh = new Mesh(vertices,indices,textures);
        meshs->push_back(mesh);
    }
}

Model::~Model()
{
    for (std::vector<Mesh*>::iterator it = meshs->begin(); it != meshs->end(); it++){
        delete *it;
    }
    meshs->clear();
    delete meshs;
}

void Model::Draw(GLProgram * program)
{
    for (std::vector<Mesh*>::iterator it = meshs->begin(); it != meshs->end(); it++){
        (*it)->Draw(program);
    }
}
