#include "Engine/Engine.hpp"

Mesh::Mesh(float * arrayVertices,float * arrayNormals,float * arrayTxtcoor,float * tangentsArray)
{
    this->arrayVertices = arrayVertices;
    this->arrayNormals = arrayNormals;
    this->arrayTxtcoor = arrayTxtcoor;
    this->tangentsArray = tangentsArray;
}

Mesh::~Mesh()
{
    free(this->arrayVertices);
    free(this->arrayNormals);
    free(this->arrayTxtcoor);
    free(this->tangentsArray);
}
