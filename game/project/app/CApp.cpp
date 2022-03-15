#include "CApp.h"
#include "yoshix_fix_function.h"
#include <iostream>

CApplication::CApplication()
	:m_pGame(nullptr),
	m_FieldOfViewY(60.0f),
	m_pPlayerMesh(nullptr),
	m_pTriangleMesh(nullptr)
{
}

CApplication::~CApplication()
{
	delete m_pGame;
}

bool InternOnStartup() 
{
	
}
bool InternOnShutdown() 
{

}


bool CApplication::InternOnCreateMeshes()
{
	static float s_TriangleVertices[][3] =
	{
		{ -4.0f, -2.0f, 0.0f, },
		{  4.0f, -2.0f, 0.0f, },
		{  0.0f,  2.0f, 0.0f, },
	};

	static int s_TriangleIndices[][3] =
	{
		{ 0, 1, 2, },
	};

	SMeshInfo MeshInfo;

	MeshInfo.m_pVertices = &s_TriangleVertices[0][0];
	MeshInfo.m_pNormals = nullptr;                      // No normals.
	MeshInfo.m_pColors = nullptr;                      // No colors.
	MeshInfo.m_pTexCoords = nullptr;                      // No texture coordinates.
	MeshInfo.m_NumberOfVertices = 3;
	MeshInfo.m_NumberOfIndices = 3;
	MeshInfo.m_pIndices = &s_TriangleIndices[0][0];
	MeshInfo.m_pTexture = nullptr;                      // No texture.

	CreateMesh(MeshInfo, &m_pTriangleMesh);

	return true;
}

bool CApplication::InternOnReleaseMeshes()
{
	ReleaseMesh(m_pTriangleMesh);

	return true;
}

bool CApplication::InternOnResize(int _Width, int _Height)
{
	float ProjectionMatrix[16];

	GetProjectionMatrix(m_FieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 100.0f, ProjectionMatrix);

	SetProjectionMatrix(ProjectionMatrix);

	return true;
}

bool CApplication::InternOnUpdate()
{
	float Eye[3];
	float At[3];
	float Up[3];

	float ViewMatrix[16];

	Eye[0] = 0.0f; At[0] = 0.0f; Up[0] = 0.0f;
	Eye[1] = 0.0f; At[1] = 0.0f; Up[1] = 1.0f;
	Eye[2] = -8.0f; At[2] = 0.0f; Up[2] = 0.0f;

	GetViewMatrix(Eye, At, Up, ViewMatrix);

	SetViewMatrix(ViewMatrix);


	return true;
}

float x = 0.0f;
float step = 0.6f;

bool CApplication::InternOnFrame()
{
	float WorldMatrix[16]; //Matrix
	float TranslationMatrix[16];
	float ScaleMatrix[16];
	float RotationMatrix[16];
	//float Vector[4];


	//1. Berechne Weltmatrix
	GetTranslationMatrix(0, 0, -1.0f, TranslationMatrix);
	//GetScaleMatrix(1,2,1, ScaleMatrix);
	GetRotationZMatrix(x, RotationMatrix);
	MulMatrix(TranslationMatrix, RotationMatrix, WorldMatrix);
	
	//2. Setze Weltmatrix
	SetWorldMatrix(WorldMatrix);
	//3. Zeichne Mesh
	DrawMesh(m_pTriangleMesh);

	x += step;

	if (x >= 360.0f)
	{
		x = 0;
	}

	return true;
}
