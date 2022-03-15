#include "CGame.h"
#include <cstdlib>
#include <iostream>

CGame::CGame(gfx::BHandle* _ppPlayerMesh)
	:_ppPlayerMesh(_ppPlayerMesh)
{
}

CGame::~CGame()
{
	delete _pPlayer;
}

void CGame::InitGame()
{
	_pPlayer = new CPlayer();
}

void CGame::RunGame(KeyState* _KeyState)
{
	_pPlayer->OnUpdate(_KeyState);
}
