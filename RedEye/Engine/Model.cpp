#include "Engine/Engine.hpp"
#include "DEBUG/Debug.hpp"

Model::Model(std::string path)
{
    meshs = new std::vector<Mesh*>();
    FILE * fb = fopen(path.c_str(), "rb");
    if(fb == NULL){
        RedLog("Model File Not Find!!!");
        return;
    }

    while(true){
        int numVertices, numFaces;

        int res = 0;
        res = fread(&numVertices, sizeof(unsigned int), 1, fb);
        if(res <= 0){
            break;
        }
        res = fread(&numFaces, sizeof(unsigned int), 1, fb);
        RedLog("\nnumVertices:%d\n",numVertices);
        RedLog("\nnumFaces:%d\n",numFaces);

        float * vertexArray = (float *)malloc(sizeof(float) * numVertices * 3);
        float * textureCoordArray = (float *)malloc(sizeof(float) * numVertices * 3);
        float * normalArray = (float *)malloc(sizeof(float) * numVertices * 3);
        float * tangentsArray = (float *)malloc(sizeof(float) * numVertices * 3);

        unsigned int * indicesArray = (unsigned int *)malloc(sizeof(unsigned int) * numFaces * 3);

        res = fread(textureCoordArray,sizeof(float) * 3,numVertices,fb);
        res = fread(vertexArray,sizeof(float) * 3,numVertices,fb);
        res = fread(normalArray,sizeof(float) * 3,numVertices,fb);
        res = fread(tangentsArray,sizeof(float) * 3,numVertices,fb);
        res = fread(indicesArray,sizeof(unsigned int),numFaces * 3,fb);
    }

    fclose(fb);
}

Model::~Model()
{
    for(int i=0;i<meshs->size();i++){
        delete (*meshs)[i];
    }
    meshs->clear();

    delete meshs;
}
