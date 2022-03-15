#include "CTriangle.h"
#include "yoshix_fix_function.h"
#include <iostream>

CTriangle::CTriangle()
{
    memcpy(PointA, StandardA, sizeof(PointA));
    memcpy(PointB, StandardB, sizeof(PointB));
    memcpy(PointC, StandardC, sizeof(PointC));
    memcpy(Color, StandardColor, sizeof(Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CTriangle::CTriangle(float _PointA[3], float _PointB[3], float _PointC[3])
{
    memcpy(PointA, _PointA, sizeof(PointA));
    memcpy(PointB, _PointB, sizeof(PointB));
    memcpy(PointC, _PointC, sizeof(PointC));
    memcpy(Color, StandardColor, sizeof(Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CTriangle::CTriangle(float _PointA[3], float _PointB[3], float _PointC[3], float _Color[4])
{
    memcpy(PointA, _PointA, sizeof(PointA));
    memcpy(PointB, _PointB, sizeof(PointB));
    memcpy(PointC, _PointC, sizeof(_PointC));
    memcpy(Color, _Color, sizeof(Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CTriangle::~CTriangle()
{
}

void CTriangle::fillVertices()
{
    Vertices[0][0] = PointA[0];
    Vertices[0][1] = PointA[1];
    Vertices[0][2] = PointA[2];
    Vertices[1][0] = PointB[0];
    Vertices[1][1] = PointB[1];
    Vertices[1][2] = PointB[2];
    Vertices[2][0] = PointC[0];
    Vertices[2][1] = PointC[1];
    Vertices[2][2] = PointC[2];
}

void CTriangle::fillColors()
{
    Colors[0][0] = Color[0];
    Colors[0][1] = Color[1];
    Colors[0][2] = Color[2];
    Colors[0][3] = Color[3];
    Colors[1][0] = Color[0];
    Colors[1][1] = Color[1];
    Colors[1][2] = Color[2];
    Colors[1][3] = Color[3];
    Colors[2][0] = Color[0];
    Colors[2][1] = Color[1];
    Colors[2][2] = Color[2];
    Colors[2][3] = Color[3];
}

void CTriangle::fillIndices()
{
    Indices[0][0] = 0;
    Indices[0][1] = 1;
    Indices[0][2] = 2;
}

gfx::SMeshInfo CTriangle::getMeshInfo() {
    gfx::SMeshInfo MeshInfo;

    MeshInfo.m_pVertices = &Vertices[0][0];
    MeshInfo.m_pNormals = nullptr;
    MeshInfo.m_pColors = &Colors[0][0];
    MeshInfo.m_pTexCoords = nullptr;
    MeshInfo.m_NumberOfVertices = 3;
    MeshInfo.m_NumberOfIndices = 3;
    MeshInfo.m_pIndices = &Indices[0][0];
    MeshInfo.m_pTexture = nullptr;

    return MeshInfo;
}
