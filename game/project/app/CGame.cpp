#include "CGame.h"
#include "CVector.h"
#include <cstdlib>
#include <random>
#include <iostream>


CGame::CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppEnemyMesh)
	:m_State(EGameState::START)
	,m_ppPlayerMesh(_ppPlayerMesh)
	,m_ppEnemyMesh(_ppEnemyMesh)
{
	m_State = EGameState::RUN;
	InitGame();
}

CGame::~CGame()
{
	delete m_pPlayer;

	for (CEnemy* e : m_pEnemies)
	{
		delete e;
	}
}

void CGame::InitGame()
{
	m_pPlayer = new CPlayer();

	float padding = 0.5f;

	for (int i = 0; i < numberOfEnemies; i++)
	{
		CreateEnemy();
		for (CEnemy* e : m_pEnemies)
		{
			e->OnUpdate();
		}
		m_pEnemies.push_back(new CEnemy((12.0f / 2) - padding, (9.0f / 2) - padding));//right top, where is enemy
	}
}

void CGame::RunGame(KeyState* _KeyState)
{
	m_pPlayer->OnUpdate(_KeyState);
	EnemyAction();

	//IF Player dead, Gameover
}

void CGame::CreateEnemy() {
	int randomNumberX = rand() % 10 + 1; //between -4 and 4, between -5 and 5
	randomNumberX -= 2;
	int randomNumberY = rand() % 10 + 1;
	randomNumberY -= 5;

	m_pEnemies.push_back(new CEnemy(randomNumberX, randomNumberY));
}

void CGame::EnemyAction() 
{
	for (CEnemy* e : m_pEnemies)
	{
		e->OnUpdate();
		//to detect if object in window
		
	}

	if (changeLevel == true) {
		SpawnEnemy();
		numberOfEnemies++;
	}
}

void CGame::SpawnEnemy() {
	for (int i = 0; i < numberOfEnemies; i++)
	{
		CreateEnemy();
	}
}
