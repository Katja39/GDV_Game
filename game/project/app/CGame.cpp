#include "CGame.h"
#include "CVector.h"
#include <cstdlib>
#include <random>
#include <iostream>


CGame::CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppEnemyMesh,gfx::BHandle* _ppLeftLineMesh)
	:m_State(EGameState::START)
	,m_ppPlayerMesh(_ppPlayerMesh)
	,m_ppEnemyMesh(_ppEnemyMesh)
	,m_ppLeftLineMesh(_ppLeftLineMesh)
{
	do {
		std::system("CLS");
		std::cout << "Welcome. Collect all the objects. If an enemy reaches the line, you lose." << std::endl;
		std::cout << std::endl;
		std::cout << "Move with WASD or with the arrow keys.\n"<< std::endl;
		std::cout << std::endl;
		std::cout << '\n' << "Press the Enter key to continue.";
	} while (std::cin.get() != '\n');
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
	delete m_pLeftLine;
}

void CGame::InitGame()
{
	m_pPlayer = new CPlayer();
	m_pLeftLine = new CLeftLine();
	SpawnEnemy();
}

void CGame::RunGame(KeyState* _KeyState)
{
	m_pPlayer->OnUpdate(_KeyState);
	EnemyAction();

	CollisionControll();

	if (score >= level*4) {
			SpawnEnemy(); //enemy gesamt = 5,10,16,23,31,40
			level++;
			SpawnNumberOfEnemies+=2;
	}
}

void CGame::FinalizedGame()
{
	CGame::~CGame();
	do {
		std::system("CLS");
		std::cout << "Congratulations!\nScore:" << score;
	} while (std::cin.get() != '\n');
}

void CGame::CreateEnemy() {
	float randomNumberX = rand() % 10 + 7; //between 10 and 7
	float randomNumberY = rand() % 8 + 0;//between 4 and -4
	randomNumberY -= 4;

	m_pEnemies.push_back(new CEnemy(randomNumberX, randomNumberY));
}

void CGame::EnemyAction() 
{
	for (CEnemy* e : m_pEnemies)
	{
		e->OnUpdate();
	}
}

void CGame::SpawnEnemy() {
	for (int i = 0; i <= SpawnNumberOfEnemies; i++)
	{
		CreateEnemy();
	}
}

void CGame::CollisionControll()
{
	for (CEnemy* e : m_pEnemies)
	{
		CPlayer* p = m_pPlayer;
		CLeftLine* l = m_pLeftLine;

			if (EnemyIsInPlayer(p, e))
			{
				m_pEnemies.erase(m_pEnemies.begin() + CVector::getVectorIndex(m_pEnemies, e));
				score += 1;
			}

			if (EnemyIsInLine(e,l))
			{
				m_State = EGameState::GAMEOVER;
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

	if ((l1x >= l2x && r1x <= r2x)&& ((l2y>=l1y&&l2y<=r1y)||(r2y>=l1y&&r2y<=r1y))) 
		return true;

	return false;
}

bool CGame::EnemyIsInLine(CEnemy* _enemy, CLeftLine* _leftLine) {
	float l1x = _enemy->CRectangle::m_PointD[0] + _enemy->m_Translation[0];
	float l1y = _enemy->CRectangle::m_PointD[1] + _enemy->m_Translation[1];
	float r1x = _enemy->CRectangle::m_PointB[0] + _enemy->m_Translation[0];
	float r1y = _enemy->CRectangle::m_PointB[1] + _enemy->m_Translation[1];

	float l2x = _leftLine->CRectangle::m_PointD[0] + _leftLine->m_Translation[0];
	float l2y = _leftLine->CRectangle::m_PointD[1] + _leftLine->m_Translation[1];
	float r2x = _leftLine->CRectangle::m_PointB[0] + _leftLine->m_Translation[0];
	float r2y = _leftLine->CRectangle::m_PointB[1] + _leftLine->m_Translation[1];

	if (l1x == r1x || l1y == r1y || l2x == r2x
		|| l2y == r2y) {
		return false;
	}
	if (l1x >= r2x || l2x >= r1x)
		return false;
	if (r1y >= l2y || r2y >= l1y)
		return false;

	return true;
}