#include "CApp.h"

CApplication::CApplication()
	:m_FieldOfViewY(60.0f),
	m_pTriangleMesh(nullptr)
{
}

CApplication::~CApplication()
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

int step = 0;

bool CApplication::InternOnFrame()
{
	float WorldMatrix[16];

	GetTranslationMatrix(0.5f, 2.0f, 1.0f, WorldMatrix);
	GetScaleMatrix(2.0f, WorldMatrix);
	GetRotationXMatrix(40, WorldMatrix);


	SetWorldMatrix(WorldMatrix);

	DrawMesh(m_pTriangleMesh);
		

	return true;
}
