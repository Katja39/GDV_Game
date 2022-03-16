#include "CGame.h"
#include <cstdlib>
#include <iostream>

CGame::CGame(gfx::BHandle* _ppPlayerMesh)
	:m_State(EGameState::START)
	,m_ppPlayerMesh(_ppPlayerMesh)
{
	m_State = EGameState::RUN;
	InitGame();
}

CGame::~CGame()
{
	delete m_pPlayer;
}

void CGame::InitGame()
{
	m_pPlayer = new CPlayer();
}

void CGame::RunGame(KeyState* _KeyState)
{
	m_pPlayer->OnUpdate(_KeyState);
}
