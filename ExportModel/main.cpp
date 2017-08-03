#include <iostream>

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

void loadMesh(aiMesh * paiMesh,int index,string out);
string intToString(int v);

int main(int argc, char *argv[])
{
    string path = "/Users/redknot/Desktop/qiu.FBX";
    string out = "/Users/redknot/Desktop/qiu/";

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return 0;
    }

    for(int i=0;i<scene->mNumMeshes;i++){
        aiMesh * paiMesh = scene->mMeshes[i];
        loadMesh(paiMesh,i,out);
    }

    return 0;
}

void loadMesh(aiMesh * paiMesh,int index,string out){

    unsigned int indicesNum = paiMesh->mNumFaces;
    unsigned int * indicesArray = (unsigned int *)malloc(sizeof(unsigned int) * indicesNum * 3);
    for(int i=0;i<indicesNum;i++){
        aiFace Face = paiMesh->mFaces[i];
        if(Face.mNumIndices != 3){
            continue;
        }
        indicesArray[i * 3] = Face.mIndices[0];
        indicesArray[i * 3 + 1] = Face.mIndices[1];
        indicesArray[i * 3 + 2] = Face.mIndices[2];
    }

    unsigned int numVertices = paiMesh->mNumVertices;
    float * vertexArray = (float *)malloc(sizeof(float) * numVertices * 3);
    for(int i=0;i<numVertices;i++){
        vertexArray[i * 3] = paiMesh->mVertices[i].x;
        vertexArray[i * 3 + 1] = paiMesh->mVertices[i].y;
        vertexArray[i * 3 + 2] = paiMesh->mVertices[i].z;
    }

    float * textureCoordArray = (float *)malloc(sizeof(float) * numVertices * 3);
    for(int i=0;i<numVertices;i++){
        textureCoordArray[i * 3] = paiMesh->mTextureCoords[0][i].x;
        textureCoordArray[i * 3 + 1] = paiMesh->mTextureCoords[0][i].y;
        textureCoordArray[i * 3 + 2] = paiMesh->mTextureCoords[0][i].z;
    }

    float * normalArray = (float *)malloc(sizeof(float) * numVertices * 3);
    for(int i=0;i<numVertices;i++){
        normalArray[i * 3] = paiMesh->mNormals[i].x;
        normalArray[i * 3 + 1] = paiMesh->mNormals[i].y;
        normalArray[i * 3 + 2] = paiMesh->mNormals[i].z;
    }

    float * tangentsArray = (float *) malloc(sizeof(float) * numVertices * 3);
    for(int i=0;i<numVertices;i++){
        tangentsArray[i * 3] = paiMesh->mTangents[i].x;
        tangentsArray[i * 3 + 1] = paiMesh->mTangents[i].y;
        tangentsArray[i * 3 + 2] = paiMesh->mTangents[i].z;
    }

    FILE * pFile = fopen((out + "part" + intToString(index)).c_str(), "wb");

    printf("numVertices:%d\n",numVertices);
    printf("indicesNum:%d\n",indicesNum);

    fwrite(&numVertices, 1, sizeof(numVertices), pFile);
    fwrite(&indicesNum, 1, sizeof(indicesNum), pFile);

    //纹理
    fwrite(textureCoordArray, 1, sizeof(float) * numVertices * 3, pFile);
    //顶点
    fwrite(vertexArray, 1, sizeof(float) * numVertices * 3, pFile);
    //法线
    fwrite(normalArray, 1, sizeof(float) * numVertices * 3, pFile);
    //正切空间
    fwrite(tangentsArray, 1, sizeof(float) * numVertices * 3, pFile);
    //Index
    fwrite(indicesArray, 1, sizeof(unsigned int) * indicesNum * 3, pFile);
}

string intToString(int v)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%u", v);

    string str = buf;
    return str;
}


