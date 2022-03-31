#include "CApplication.h"
#include "yoshix_fix_function.h"
#include <iostream>
#include <cstdlib>

CApplication::CApplication()
	:m_pGame(nullptr)
	,m_FieldOfViewY(60.0f)
	,m_pPlayerMesh(nullptr)
	,m_pEnemyMesh(nullptr)
	,m_pPowerUpMesh(nullptr)
	,m_pBackgroundMesh(nullptr)
	,m_pLeftLineMesh(nullptr)
{
	float WIDTH = 11.94f;// /1.005
	float HEIGHT = 8.955f;

	float BackgroundA[3] = { -WIDTH / 2, -HEIGHT / 2, 0 };
	float BackgroundB[3] = { WIDTH / 2, -HEIGHT / 2, 0 };
	float BackgroundC[3] = { WIDTH / 2,  HEIGHT / 2, 0 };
	float BackgroundD[3] = { -WIDTH / 2,  HEIGHT / 2, 0 };

	float color = 0.02f;
	float BackgroundColor[4] = { color,color,color, color };//darkgrey

	m_Background = new CRectangle(BackgroundA, BackgroundB, BackgroundC, BackgroundD, BackgroundColor);
}

CApplication::~CApplication()
{
	delete m_pGame;
	delete m_Background;
}

bool CApplication::InternOnStartup()
{
	m_pGame = new CGame(&m_pPlayerMesh, &m_pEnemyMesh,&m_pLeftLineMesh,&m_pPowerUpMesh);
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
	for (CPowerUp* p : m_pGame->m_pPowerUp)
	{
		gfx::CreateMesh(p->getMeshInfo(), &m_pPowerUpMesh);
	}

	gfx::CreateMesh(m_pGame->m_pLeftLine->getMeshInfo(), &m_pLeftLineMesh);

	gfx::CreateMesh(m_Background->getMeshInfo(), &m_pBackgroundMesh);

	return true;
}

bool CApplication::InternOnReleaseMeshes()
{
	gfx::ReleaseMesh(m_pPlayerMesh);
	gfx::ReleaseMesh(m_pEnemyMesh);
	gfx::ReleaseMesh(m_pLeftLineMesh);
	gfx::ReleaseMesh(m_pBackgroundMesh);
	gfx::ReleaseMesh(m_pPowerUpMesh);

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
			m_KeyState.isWdown = _IsKeyDown; // 38 = up arrow
		}
		if (_Key == 'S' || _Key == 40){      //40 = down arrow
			m_KeyState.isSdown = _IsKeyDown; 
		}
		if (_Key == 'D' || _Key == 39) {    // 39 = right arrow
			m_KeyState.isDdown = _IsKeyDown;
		}
		if (_Key == 'A' || _Key == 37) {    //37 = left arrow
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
	
	// 
	//Player
	//

	float TranslationMatrix[16];
	float ScaleMatrix[16];
	gfx::GetTranslationMatrix(m_pGame->m_pPlayer->m_Translation[0], m_pGame->m_pPlayer->m_Translation[1], m_pGame->m_pPlayer->m_Translation[2], TranslationMatrix);
	gfx::GetScaleMatrix(m_pGame->m_pPlayer->m_Scale[0], m_pGame->m_pPlayer->m_Scale[1], m_pGame->m_pPlayer->m_Scale[2], ScaleMatrix);
	gfx::MulMatrix(ScaleMatrix,TranslationMatrix, WorldMatrix);
	gfx::SetWorldMatrix(WorldMatrix);
	gfx::DrawMesh(m_pPlayerMesh);

	//
	//Enemy
	//

	 for (CEnemy* e : m_pGame->m_pEnemies) {
        gfx::GetTranslationMatrix(e->m_Translation[0], e->m_Translation[1], e->m_Translation[2], WorldMatrix);
        gfx::SetWorldMatrix(WorldMatrix);
        gfx::DrawMesh(m_pEnemyMesh);
    }
	 //
	 //LeftLine
	 //

	 gfx::GetTranslationMatrix(m_pGame->m_pLeftLine->m_Translation[0], m_pGame->m_pLeftLine->m_Translation[1], m_pGame->m_pLeftLine->m_Translation[2], WorldMatrix);
	 gfx::SetWorldMatrix(WorldMatrix);
	 gfx::DrawMesh(m_pLeftLineMesh);
	 
	 //
	 //Power Up
	 //

	 float RotationMatrix[16];
	 for (CPowerUp* p : m_pGame->m_pPowerUp) {
		 gfx::GetTranslationMatrix(p->m_Translation[0], p->m_Translation[1], p->m_Translation[2], TranslationMatrix);
		 gfx::GetRotationZMatrix(p->m_Rotation[2], RotationMatrix);
		 gfx::MulMatrix(RotationMatrix, TranslationMatrix,WorldMatrix);
		 gfx::SetWorldMatrix(WorldMatrix);
		 gfx::DrawMesh(m_pPowerUpMesh);
	 }
	 //
	 //Background
	 //

	  gfx::GetTranslationMatrix(m_Background->m_Translation[0], m_Background->m_Translation[1], m_Background->m_Translation[2], WorldMatrix);
	  gfx::SetWorldMatrix(WorldMatrix);
	  gfx::DrawMesh(m_pBackgroundMesh);
	return true;
}
