#include "CApplication.h"
#include "yoshix_fix_function.h"
#include <iostream>
#include <cstdlib>

CApplication::CApplication()
	:m_pGame(nullptr)
	,m_FieldOfViewY(60.0f)
	,m_pPlayerMesh(nullptr)
	,m_pEnemyMesh(nullptr)
	,m_pBottomLineMesh(nullptr)
	,m_pBackgroundMesh(nullptr)
{
	float WIDTH = 12.0f;
	float HEIGHT = 9.0f;

	float BackgroundA[3] = { -WIDTH / 2, -HEIGHT / 2, 0 };
	float BackgroundB[3] = { WIDTH / 2, -HEIGHT / 2, 0 };
	float BackgroundC[3] = { WIDTH / 2,  HEIGHT / 2, 0 };
	float BackgroundD[3] = { -WIDTH / 2,  HEIGHT / 2, 0 };

	int color = 0.1;
	float BackgroundColor[4] = { color,color,color, 1.0f };

	m_Background = new CRectangle(BackgroundA, BackgroundB, BackgroundC, BackgroundD, BackgroundColor);

	float LineWidth = 0.05f;

	float BottomLineA[3] = { -LineWidth,-HEIGHT/2, 0 };
	float BottomLineB[3] = { LineWidth, -HEIGHT/2, 0 };
	float BottomLineC[3] = { LineWidth, HEIGHT/2, 0 };
	float BottomLineD[3] = { -LineWidth, HEIGHT/2, 0 };
	float BottomLineColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

	m_LeftLine = new CRectangle(BottomLineA, BottomLineB, BottomLineC, BottomLineD, BottomLineColor);
	m_LeftLine->m_Translation[0] = -5.75f;
}

CApplication::~CApplication()
{
	delete m_pGame;
	delete m_Background;
	delete m_LeftLine;
}

bool CApplication::InternOnStartup()
{
	m_pGame = new CGame(&m_pPlayerMesh, &m_pEnemyMesh);
	float ClearColor[4] = { 0.0f, 0.0f, 0.2f, 0.2f, };
	gfx::SetClearColor(ClearColor);

	return true;
}
bool CApplication::InternOnShutdown()
{
	return true;
}

bool CApplication::InternOnCreateMeshes()
{
	gfx::CreateMesh(m_pGame->m_pPlayer->getMeshInfo(), &m_pPlayerMesh);

	for (CEnemy* e : m_pGame->m_pEnemies)
	{
		gfx::CreateMesh(e->getMeshInfo(), &m_pEnemyMesh);
	}

	gfx::CreateMesh(m_LeftLine->getMeshInfo(), &m_pBottomLineMesh);
	gfx::CreateMesh(m_Background->getMeshInfo(), &m_pBackgroundMesh);

	return true;
}

bool CApplication::InternOnReleaseMeshes()
{
	gfx::ReleaseMesh(m_pPlayerMesh);
	gfx::ReleaseMesh(m_pEnemyMesh);
	gfx::ReleaseMesh(m_pBottomLineMesh);
	gfx::ReleaseMesh(m_pBackgroundMesh);

	return true;
}

bool CApplication::InternOnResize(int _Width, int _Height)
{
	float ProjectionMatrix[16];

	gfx::GetProjectionMatrix(m_FieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 100.0f, ProjectionMatrix);

	gfx::SetProjectionMatrix(ProjectionMatrix);

	return true;
}

bool CApplication::InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown)
{
		if (_Key == 'W' || _Key == 38){
			m_KeyState.isWdown = _IsKeyDown; // 38 is the UP Arrow
		}
		if (_Key == 'S' || _Key == 40){
			m_KeyState.isSdown = _IsKeyDown; // 39 is the DOWN Arrow
		}
		if (_Key == 'D' || _Key == 39) {
			m_KeyState.isDdown = _IsKeyDown;
		}
		if (_Key == 'A' || _Key == 37) {
			m_KeyState.isAdown = _IsKeyDown;
		}
		
		return true;
	
}

bool CApplication::InternOnUpdate()
{
	float Eye[3];
	float At[3];
	float Up[3];

	float ViewMatrix[16];

	switch (m_pGame->m_State)
	{
	case EGameState::START:
		break;
	case EGameState::RUN:
		m_pGame->RunGame(&m_KeyState);
		break;
	case EGameState::GAMEOVER:
		m_pGame->FinalizedGame();
		break;
	}

	Eye[0] = 0.0f; At[0] = 0.0f; Up[0] = 0.0f;
	Eye[1] = 0.0f; At[1] = 0.0f; Up[1] = 1.0f;
	Eye[2] = -8.0f; At[2] = 0.0f; Up[2] = 0.0f;

	gfx::GetViewMatrix(Eye, At, Up, ViewMatrix);

	gfx::SetViewMatrix(ViewMatrix);

	return true;
}

bool CApplication::InternOnFrame()
{
	float WorldMatrix[16];

	// -----------------------------------------------------------------------------
	// Set the position of the mesh in the world and draw it.
	// -----------------------------------------------------------------------------
	//Player
	gfx::GetTranslationMatrix(m_pGame->m_pPlayer->m_Translation[0], m_pGame->m_pPlayer->m_Translation[1], m_pGame->m_pPlayer->m_Translation[2], WorldMatrix);
	gfx::SetWorldMatrix(WorldMatrix);
	gfx::DrawMesh(m_pPlayerMesh);

	//Enemy
	 for (CEnemy* e : m_pGame->m_pEnemies) {
        gfx::GetTranslationMatrix(e->m_Translation[0], e->m_Translation[1], e->m_Translation[2], WorldMatrix);
        gfx::SetWorldMatrix(WorldMatrix);
        gfx::DrawMesh(m_pEnemyMesh);
    }

	  gfx::GetTranslationMatrix(m_LeftLine->m_Translation[0], m_LeftLine->m_Translation[1], m_LeftLine->m_Translation[2], WorldMatrix);
	  gfx::SetWorldMatrix(WorldMatrix);
	  gfx::DrawMesh(m_pBottomLineMesh);

	  gfx::GetTranslationMatrix(m_Background->m_Translation[0], m_Background->m_Translation[1], m_Background->m_Translation[2], WorldMatrix);
	  gfx::SetWorldMatrix(WorldMatrix);
	  gfx::DrawMesh(m_pBackgroundMesh);

	return true;
}
