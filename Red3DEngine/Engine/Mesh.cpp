#include "Engine.hpp"

Mesh::Mesh(std::vector<Vertex*> * vertices, std::vector<GLuint> * indices, std::vector<Texture*> * textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    arrayVertices = (float *)malloc(sizeof(float) * vertices->size() * 3);
    arrayNormals = (float *)malloc(sizeof(float) * vertices->size() * 3);
    arrayTxtcoor = (float *)malloc(sizeof(float) * vertices->size() * 3);

    arrayIndices = (unsigned int * ) malloc(sizeof(unsigned int) * indices->size());

    for(int i=0;i<indices->size();i++){
        arrayIndices[i] = (*indices)[i];
    }

    for(int i=0;i<vertices->size();i++){
        arrayVertices[i * 3] = (*vertices)[i]->Position_x;
        arrayVertices[i * 3 + 1] = (*vertices)[i]->Position_y;
        arrayVertices[i * 3 + 2] = (*vertices)[i]->Position_z;

        arrayNormals[i * 3] = (*vertices)[i]->Normal_x;
        arrayNormals[i * 3 + 1] = (*vertices)[i]->Normal_y;
        arrayNormals[i * 3 + 2] = (*vertices)[i]->Normal_z;

        arrayTxtcoor[i * 3] = (*vertices)[i]->TexCoords_x;
        arrayTxtcoor[i * 3 + 1] = (*vertices)[i]->TexCoords_y;
        arrayTxtcoor[i * 3 + 2] = 0.0f;
    }

    vao = new GLVAO();

    vao->AddVBO(arrayVertices,sizeof(float) * vertices->size() * 3,0,3);
    vao->AddVBO(arrayNormals,sizeof(float) * vertices->size() * 3,1,3);
    vao->AddVBO(arrayTxtcoor,sizeof(float) * vertices->size() * 3,2,3);

    vao->SetEBO(arrayIndices,sizeof(unsigned int) * indices->size());
}

Mesh::~Mesh()
{
    vao->DeleteVAO();
    for (std::vector<Vertex*>::iterator it = vertices->begin(); it != vertices->end(); it++){
        delete *it;
    }
    vertices->clear();
    delete vertices;

    for (std::vector<Texture *>::iterator it = textures->begin(); it != textures->end(); it++){
        delete *it;
    }
    textures->clear();
    delete textures;

    delete vao;
}

void Mesh::Draw(GLProgram * program)
{
    program->UseProgram();
    vao->DrawVAO();
}
