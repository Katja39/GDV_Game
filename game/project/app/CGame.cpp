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
	//do {
	//	std::system("CLS");
	//	std::cout << "Sammel alle Objekte auf. Wenn ein Gegener die Linie trifft, hast du verloren" << std::endl;
	//	std::cout << std::endl;
	//	std::cout << "Move with 'A' and 'D' or with the arrow keys.\n"<< std::endl;
	//	std::cout << std::endl;
	//	std::cout << '\n' << "Press the Enter key to continue.";
	//} while (std::cin.get() != '\n');
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
	float l1x = _player->CTriangle::m_PointA[0] + _player->m_Translation[0];//Ax
	float l1y = _player->CTriangle::m_PointA[1] + _player->m_Translation[1];//Ay
	float r1x = _player->CTriangle::m_PointC[0] + _player->m_Translation[0];//Cx
	float r1y = _player->CTriangle::m_PointC[1] + _player->m_Translation[1];//Cy

	float l2x = _enemy->CRectangle::m_PointD[0] + _enemy->m_Translation[0];//Dx
	float l2y = _enemy->CRectangle::m_PointD[1] + _enemy->m_Translation[1];//Dy
	float r2x = _enemy->CRectangle::m_PointB[0] + _enemy->m_Translation[0];//Bx
	float r2y = _enemy->CRectangle::m_PointB[1] + _enemy->m_Translation[1];//By

	//std::cout << l1x << " " << l1y << " " << r1x << " " << r1y;
	//std::cout << l2x << " " << l2y << " " << r2x << " " << r2y<<"\n";

	if ((l1x > l2x || r1x > r2x)&& ((l2y>=l1y&&l2y<=r1y)||(r2y>=l1y&&r2y<=r1y))) 
		return true;

	return false;
}
