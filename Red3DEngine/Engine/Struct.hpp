#pragma once

/*
 *
 * 顶点
 *
 */
typedef struct Vertex
{
    float Position_x;
    float Position_y;
    float Position_z;

    float Normal_x;
    float Normal_y;
    float Normal_z;

    float Tangents_x;
    float Tangents_y;
    float Tangents_z;

    float TexCoords_x;
    float TexCoords_y;
}Vertex;

typedef struct Mouse{
    double x;
    double y;
}Mouse;


typedef struct Vector2{
    float x;
    float y;
}Vector2;

typedef struct Vector3{
    float x;
    float y;
    float z;
}Vector3;
