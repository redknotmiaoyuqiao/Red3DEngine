#include <iostream>

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

void loadMesh(aiMesh * paiMesh,int index,FILE * pFile);
string intToString(int v);

float x[] = { 0.55, -0.32,  0.32, -0.46,  0.46, -0.46,  0.46, -0.79,  0.79, -0.63,  0.63, -0.64,  0.64, -0.54,  0.54, -0.25,  0.25, -0.27,  0.27, -0.44,  0.44, -0.45,  0.45, -1.04,  1.04, -0.88,  0.88, -0.86,  0.86, -0.66,  0.66, -0.66,  0.66, -0.16,  0.16, -0.26,  0.26, -0.38,  0.38, -0.26,  0.26, -0.12,  0.12, -0.47,  0.47, -0.28,  0.28, -0.29,  0.29, -0.11,  0.11, -0.13,  0.13, -0.39,  0.39, -0.12,  0.12, -0.12,  0.12, -1.56,  1.56, -1.56,  1.56, -1.56,  1.56, -1.55,  1.55, -1.53,  1.53, -1.51,  1.51, -1.46,  1.46, -1.40,  1.40, -1.30,  1.30, -1.18,  1.18, -1.02,  1.02, -0.86,  0.86, -0.68,  0.68, -0.52,  0.52, -0.35,  0.35, -0.17,  0.17,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00,  0.00 };
float y[] = {-0.57, -0.61, -0.61, -0.70, -0.70, -0.57, -0.57, -0.63, -0.63, -0.69, -0.69, -0.58, -0.58, -0.63, -0.63, -1.08, -1.08, -0.99, -0.99, -1.14, -1.14, -1.01, -1.01, -0.96, -0.96, -1.11, -1.11, -0.98, -0.98, -1.16, -1.16, -1.01, -1.01, -0.66, -0.66, -0.13, -0.13,  0.07,  0.07,  0.14,  0.14,  0.16,  0.16,  0.59,  0.59,  0.49,  0.49,  0.70,  0.70,  0.43,  0.43,  0.74,  0.74,  0.60,  0.60,  0.56,  0.56,  0.60,  0.60, -0.80, -0.80, -0.59, -0.59, -0.38, -0.38, -0.16, -0.16,  0.05,  0.05,  0.26,  0.26,  0.46,  0.46,  0.66,  0.66,  0.85,  0.85,  1.00,  1.00,  1.13,  1.13,  1.23,  1.23,  1.30,  1.30,  1.35,  1.35,  1.38,  1.38,  1.37,  1.37,  1.34,  0.75,  0.60,  0.56,  0.46,  0.19, -0.06, -0.26, -0.47, -0.69,  0.00 };
float z[] = { 0.01,  0.03,  0.03,  0.00,  0.00,  0.00,  0.00,  0.13,  0.13,  0.00,  0.00,  0.04,  0.04,  0.01,  0.01, -0.20, -0.20, -0.14, -0.14, -0.16, -0.16, -0.10, -0.10,  0.24,  0.24,  0.05,  0.05,  0.07,  0.07, -0.08, -0.08, -0.05, -0.05, -0.11, -0.11, -0.20, -0.20, -0.11, -0.11, -0.24, -0.24, -0.32, -0.32, -0.07, -0.07, -0.25, -0.25, -0.20, -0.20, -0.35, -0.35, -0.28, -0.28, -0.08, -0.08, -0.27, -0.27, -0.26, -0.26,  1.27,  1.27,  1.25,  1.25,  1.23,  1.23,  1.21,  1.21,  1.19,  1.19,  1.17,  1.17,  1.15,  1.15,  1.10,  1.10,  1.04,  1.04,  0.95,  0.95,  0.83,  0.83,  0.68,  0.68,  0.53,  0.53,  0.37,  0.37,  0.20,  0.20,  0.08,  0.08, -0.04, -0.31, -0.29, -0.30, -0.36, -0.35, -0.59, -0.55, -0.40, -0.26,  1.27};
int main(int argc, char *argv[])
{

    //string path = "/Users/redknot/Red3DEngine/3dModel/Tea/tea.FBX";
    string path = "/Users/redknot/Red3DEngine/3dModel/nanosuit/nanosuit.obj";
    //string out = "/Users/redknot/Red3DEngine/3dModel/Tea/model/";

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return 0;
    }


    //FILE * pFile = fopen("/Users/redknot/Red3DEngine/3dModel/Tea/tea.redmeshs", "wb");
    FILE * pFile = fopen("/Users/redknot/Red3DEngine/3dModel/nanosuit/nanosuit.redmeshs", "wb");

    for(int i=0;i<scene->mNumMeshes;i++){
        aiMesh * paiMesh = scene->mMeshes[i];
        loadMesh(paiMesh,i,pFile);
    }

    return 0;
}

void loadMesh(aiMesh * paiMesh,int index,FILE * pFile){

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

    //FILE * pFile = fopen((out + "part" + intToString(index)).c_str(), "wb");

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


