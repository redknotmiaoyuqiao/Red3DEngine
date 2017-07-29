#include "Engine.hpp"

Mesh::Mesh(std::vector<Vertex*> * vertices, std::vector<GLuint> * indices)
{
    this->vertices = vertices;
    this->indices = indices;

    arrayVertices = (float *)malloc(sizeof(float) * vertices->size() * 3);
    arrayNormals = (float *)malloc(sizeof(float) * vertices->size() * 3);
    arrayTxtcoor = (float *)malloc(sizeof(float) * vertices->size() * 3);
    tangentsArray = (float *)malloc(sizeof(float) * vertices->size() * 3);

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

        tangentsArray[i * 3] = (*vertices)[i]->Tangents_x;
        tangentsArray[i * 3 + 1] = (*vertices)[i]->Tangents_y;
        tangentsArray[i * 3 + 2] = (*vertices)[i]->Tangents_z;
    }

    /*
    FILE *fp = fopen("/Users/redknot/Desktop/Face.mesh", "rb");
    int n, nt;
    fread(&n, 4, 1, fp);
    fread(&nt, 4, 1, fp);
    printf("%d vertices, %d triangles\n", n, nt);
    float   *XY = new float[n*2],
            *XYZ = new float[n*3];
    int     *idx = new int[nt*3];
    fread(XY, 4*2, n, fp);
    fread(XYZ, 4*3, n, fp);
    fread(idx, 4*3, nt, fp);
    fclose(fp);



    vao = new GLVAO();

    vao->AddVBO(XYZ,4*3*n,0,3);

    vao->AddVBO(XY,4*2*n,2,2);

    vao->SetEBO((GLuint*)idx,4*3*nt);
    */


    vao = new GLVAO();
    vao->AddVBO(arrayVertices,sizeof(float) * vertices->size() * 3,0,3);
    vao->AddVBO(arrayNormals,sizeof(float) * vertices->size() * 3,1,3);
    vao->AddVBO(arrayTxtcoor,sizeof(float) * vertices->size() * 3,2,3);
    vao->AddVBO(tangentsArray,sizeof(float) * vertices->size() * 3,3,3);
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

    delete vao;

    free(arrayVertices);
    free(arrayNormals);
    free(arrayTxtcoor);
    free(tangentsArray);

    delete this->material;
}

void Mesh::setMaterial(Material * material)
{
    this->material = material;
}

void Mesh::Draw(GLProgram * program)
{
    program->UseProgram();
    this->material->UseMaterial(program);
    vao->DrawVAO();
}
