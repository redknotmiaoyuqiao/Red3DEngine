#include "Engine.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(std::string path)
{
    meshs = new std::vector<Mesh*>();

    int index = 0;
    while(true){
        std::string file_path = path + "/part" + intToString(index);

        RedLog("wwwwwwwww:\n%s\n\n",file_path.c_str());

        FILE * fb = fopen(file_path.c_str(), "rb");
        if(fb == NULL){
            break;
        }

        int numVertices, numFaces;

        fread(&numVertices, sizeof(unsigned int), 1, fb);
        fread(&numFaces, sizeof(unsigned int), 1, fb);
        RedLog("\nnumVertices:%d\n",numVertices);
        RedLog("\nnumFaces:%d\n",numFaces);

        float * vertexArray = (float *)malloc(sizeof(float) * numVertices * 3);
        float * textureCoordArray = (float *)malloc(sizeof(float) * numVertices * 3);
        float * normalArray = (float *)malloc(sizeof(float) * numVertices * 3);

        unsigned int * indicesArray = (unsigned int *)malloc(sizeof(unsigned int) * numFaces * 3);

        fread(textureCoordArray,sizeof(float) * 3,numVertices,fb);
        fread(vertexArray,sizeof(float) * 3,numVertices,fb);
        fread(normalArray,sizeof(float) * 3,numVertices,fb);
        fread(indicesArray,sizeof(unsigned int),numFaces * 3,fb);

        fclose(fb);


        std::vector<Vertex*> * vertices = new std::vector<Vertex*>();
        std::vector<GLuint> * indices = new std::vector<GLuint>();

        for(int i=0;i<numVertices;i++){
            Vertex * v = new Vertex;
            v->Position_x = vertexArray[i * 3];
            v->Position_y = vertexArray[i * 3 + 1];
            v->Position_z = vertexArray[i * 3 + 2];

            v->Normal_x = normalArray[i * 3];
            v->Normal_y = normalArray[i * 3 + 1];
            v->Normal_z = normalArray[i * 3 + 2];

            v->TexCoords_x = textureCoordArray[i * 3];
            v->TexCoords_y = textureCoordArray[i * 3 + 1];
            vertices->push_back(v);
        }

        for(int i=0;i<numFaces * 3;i++){
            indices->push_back(indicesArray[i]);
        }

        free(vertexArray);
        free(textureCoordArray);
        free(normalArray);
        free(indicesArray);

        Material * mm = new Material();

        std::string imagePath = path + "/part" + intToString(index);

        GLTexture * ambient = new GLTexture();
        ambient->LoadImage((char *)(imagePath + ".dif.png").c_str());

        GLTexture * specular = new GLTexture();
        specular->LoadImage((char *)(imagePath + ".spec.png").c_str());

        GLTexture * normal = new GLTexture();
        normal->LoadImage((char *)(imagePath + ".ddn.png").c_str());

        mm->setAmbient(ambient);
        mm->setSpecular(specular);
        mm->setNormalMap(normal);
        mm->setShininess(80.0f);

        Mesh * mesh = new Mesh(vertices,indices);
        mesh->setMaterial(mm);
        meshs->push_back(mesh);

        index++;
    }
}

/*
Model::Model(std::string path)
{
    meshs = new std::vector<Mesh*>();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return;
    }

    RedLog("-------------LoadModel Start-------------\n");
    RedLog("Path:%s\n",path.c_str());
    RedLog("Mesh Number:%d\n",scene->mNumMeshes);
    for(int i=0;i<scene->mNumMeshes;i++){
        aiMesh * paiMesh = scene->mMeshes[i];
        RedLog("\n");
        RedLog("Mesh:%d\n",i + 1);
        RedLog("Vertices Number:%d\n",paiMesh->mNumVertices);
        RedLog("Faces Number:%d\n",paiMesh->mNumFaces);
    }
    RedLog("-------------LoadModel End---------------\n\n");

    for(int i=0;i<scene->mNumMeshes;i++){
        aiMesh * paiMesh = scene->mMeshes[i];

        //将会被Mesh的析构函数释放
        std::vector<Vertex*> * vertices = new std::vector<Vertex*>();
        std::vector<GLuint> * indices = new std::vector<GLuint>();

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

        Material * mm = new Material();

        if(i == 0){
            GLTexture * ambient = new GLTexture();
            ambient->LoadImage("/Users/redknot/Desktop/nanosuit/glass_dif.png");

            GLTexture * specular = new GLTexture();
            specular->LoadImage("/Users/redknot/Desktop/nanosuit/glass_dif.png");

            GLTexture * normal = new GLTexture();
            normal->LoadImage("/Users/redknot/Desktop/Cubeq/Cube/glass_ddn.png");

            mm->setAmbient(ambient);
            mm->setSpecular(specular);
            mm->setNormalMap(normal);
            mm->setShininess(80.0f);
        }

        if(i == 1){
            GLTexture * ambient = new GLTexture();
            ambient->LoadImage("/Users/redknot/Desktop/nanosuit/leg_dif.png");

            GLTexture * specular = new GLTexture();
            specular->LoadImage("/Users/redknot/Desktop/nanosuit/leg_showroom_spec.png");

            GLTexture * normal = new GLTexture();
            normal->LoadImage("/Users/redknot/Desktop/Cubeq/Cube/Cube_DefaultMaterial_Nomal.png");

            mm->setAmbient(ambient);
            mm->setSpecular(specular);
            mm->setNormalMap(normal);
            mm->setShininess(80.0f);
        }



        Mesh * mesh = new Mesh(vertices,indices);
        mesh->setMaterial(mm);
        meshs->push_back(mesh);
    }


}
*/
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
