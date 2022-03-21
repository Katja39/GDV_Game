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
	int numberOfEnemies = 1;


	for (int i = 0; i < numberOfEnemies; i++)
	{
		for (CEnemy* e : m_pEnemies)
		{
			e->OnUpdate();
		}
		m_pEnemies.push_back(new CEnemy((12.0f/2) -padding , (9.0f / 2) - padding));//right top, where is enemy
	}
}

void CGame::RunGame(KeyState* _KeyState)
{
	m_pPlayer->OnUpdate(_KeyState);
	EnemyAction();

	//IF Player dead, Gameover
}

void CGame::CreateEnemy() {
	float padding = 0.5f;
	m_pEnemies.push_back(new CEnemy((12.0f / 2) - padding, (9.0f / 2) - padding)); //right top
}

void CGame::EnemyAction() 
{
	m_Ticks++;
	if (m_Ticks == m_MaxTicks)
	{
		for (CEnemy* e : m_pEnemies)
		{
			e->OnUpdate();
		}
			CreateEnemy();
			m_Speed++;
			if (m_Speed >= m_MaxSpeedInterval)
			{
				m_Speed = 0;
				
			}
		
		m_Ticks = 0;

	}
}
