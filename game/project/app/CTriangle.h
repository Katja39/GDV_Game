#pragma once
#include "CObjectMesh.h"

class CTriangle:public CObjectMesh{
public:
    static constexpr float StandardA[3] = { -4.0f, -2.0f, 0.0f };
    static constexpr float StandardB[3] = { 4.0f, -2.0f, 0.0f };
    static constexpr float StandardC[3] = { 0.0f,  2.0f, 0.0f };
    static constexpr float StandardColor[4] = { 1.0f,  1.0f, 1.0f, 1.0f };

public:
    float PointA[3];
    float PointB[3];
    float PointC[3];
    float Color[4];
    float Vertices[3][3];
    float Colors[3][4];
    int   Indices[1][3];

public:
    CTriangle();
    CTriangle(float _PointA[3], float _PointB[3], float _PointC[3]);
    CTriangle(float _PointA[3], float _PointB[3], float _PointC[3], float _Color[4]);
    ~CTriangle();
    gfx::SMeshInfo getMeshInfo() override;
protected:
    void fillVertices();
    void fillColors();
    void fillIndices();
};
