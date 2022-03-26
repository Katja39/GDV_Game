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

	CollisionControll();
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

//TODO Collider



void CGame::CollisionControll()
{
	for (CEnemy* e : m_pEnemies)
	{
		CPlayer* p = m_pPlayer;
		
			if (EnemyIsInPlayer(p, e))
			{
				m_pEnemies.erase(m_pEnemies.begin() + CVector::getVectorIndex(m_pEnemies, e));
			}
		
	}
}

bool CGame::EnemyIsInPlayer(CPlayer* _player, CEnemy* _enemy)
{
	float l1x = _player->CTriangle::m_PointA[0] + _player->m_Translation[0];//A;x
	float l1y = _player->CTriangle::m_PointA[1] + _player->m_Translation[1];//A;y
	float r1x = _player->CTriangle::m_PointC[0] + _player->m_Translation[0];//C;x
	float r1y = _player->CTriangle::m_PointC[1] + _player->m_Translation[1];//C;y

	float l2x = _enemy->CRectangle::m_PointD[0] + _enemy->m_Translation[0];
	float l2y = _enemy->CRectangle::m_PointD[1] + _enemy->m_Translation[0];
	float r2x = _enemy->CRectangle::m_PointB[0] + _enemy->m_Translation[0];
	float r2y = _enemy->CRectangle::m_PointB[1] + _enemy->m_Translation[1];

	//std::cout << l1x << " " << l1y << " " << r1x << " " << r1y;
	//std::cout << l2x << " " << l2y << " " << r2x << " " << r2y<<"\n";
	
	if (r1x >= r2x || l2x >= r1x)//-5,25 < -0.37; -5
		return false;

	return true;
}
