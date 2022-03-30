#include "CGame.h"
#include "CVector.h"
#include <cstdlib>
#include <random>
#include <iostream>


CGame::CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppEnemyMesh, gfx::BHandle* _ppPowerUpMesh,gfx::BHandle* _ppLeftLineMesh)
	:m_State(EGameState::START)
	,m_ppPlayerMesh(_ppPlayerMesh)
	,m_ppEnemyMesh(_ppEnemyMesh)
	,m_ppPowerUpMesh(_ppPowerUpMesh)
	,m_ppLeftLineMesh(_ppLeftLineMesh)
{
	do {
		std::system("CLS");
		std::cout << "Welcome. Collect all the objects. If an enemy reaches the line, you lose." << std::endl;
		std::cout << std::endl;
		std::cout << "Collect the yellow power-ups to increase the size of the player.\n" << std::endl;
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
	for (CPowerUp* p : m_pPowerUp)
	{
		delete p;
	}
	delete m_pLeftLine;
}

void CGame::InitGame()
{
	m_pPlayer = new CPlayer();
	m_pLeftLine = new CLeftLine();
	SpawnEnemy();
	SpawnPowerUp();
}

void CGame::RunGame(KeyState* _KeyState)
{
	m_pPlayer->OnUpdate(_KeyState);
	EnemyAction();
	PowerUpAction();

	CollisionControllEnemy();
	CollisionControllPowerUp();

	//Level
	if (score >= round*3&&score<30) {
			SpawnEnemy(); //enemy gesamt = 3,7,12,17,23,30,38,47,57,68,80
			round++;
			SpawnNumberOfEnemies++;
			if(power==false){
			SpawnPowerUp();
			}
	}
	if (score == 50) {
		SpawnNumberOfEnemies = 3;
		enemySpeed = 0.03;
		level++;
	}
	if (score>60&&score >= round * 5 && score < 90) {
		SpawnEnemy();
		round++;
		SpawnNumberOfEnemies++;
		if (power == false) {
			SpawnPowerUp();
		}
	}
	if (score == 120) {
		SpawnNumberOfEnemies = 4;
		enemySpeed = 0.05;
		level++;
	}
	if (score > 100 && score >= round * 4 && score < 150) {
		SpawnEnemy();
		round++;
		SpawnNumberOfEnemies++;
		if (power == false) {
			SpawnPowerUp();
		}
	}


}

void CGame::FinalizedGame()
{
	do {
		std::system("CLS");
		std::cout << "Congratulations!\nScore:" << score;
		std::cout << "\nLevel:" << level;
	} while (std::cin.get() != '\n');
}

void CGame::CreateEnemy() {
	float randomNumberX = rand() % 10 + 7; //between 10 and 7
	float randomNumberY = rand() % 8 + 0;//between 4 and -4
	randomNumberY -= 4;

	m_pEnemies.push_back(new CEnemy(randomNumberX, randomNumberY));
}
void CGame::CreatePowerUp() {
	float randomNumberX = rand() % 10 + 7; //between 10 and 7
	float randomNumberY = rand() % 8 + 0;//between 4 and -4
	randomNumberY -= 4;
	m_pPowerUp.push_back(new CPowerUp(randomNumberX, randomNumberY));
}

void CGame::EnemyAction() 
{
	for (CEnemy* e : m_pEnemies)
	{
		e->OnUpdate();
	}
}

void CGame::PowerUpAction()
{
	for (CPowerUp* p : m_pPowerUp)
	{
		p->OnUpdate();
	}
}

void CGame::SpawnEnemy() {
	for (int i = 0; i <= SpawnNumberOfEnemies; i++)
	{
		ChangeEnemySpeed();
		CreateEnemy();
	}
}

void CGame::SpawnPowerUp() {
	CreatePowerUp();
}

void CGame::CollisionControllEnemy()
{
	for (CEnemy* e : m_pEnemies)
	{
		CPlayer* p = m_pPlayer;
		CLeftLine* l = m_pLeftLine;
			if (EnemyIsInPlayer(p, e))
			{
				if (power == true) {
					remainingPower--;
				}
				m_pEnemies.erase(m_pEnemies.begin() + CVector::getVectorIndex(m_pEnemies, e));
				score += 1;
			}
			if (EnemyIsInLine(e,l))
			{
				m_State = EGameState::GAMEOVER;
			}
	}
}

void CGame::CollisionControllPowerUp() 
{
	for (CPowerUp* pu : m_pPowerUp)
	{
		CPlayer* p = m_pPlayer;
		CLeftLine* l = m_pLeftLine;
		if (PlayerIsInPowerUp(p, pu)) {
			m_pPowerUp.erase(m_pPowerUp.begin() + CVector::getVectorIndex(m_pPowerUp, pu));
			power = true;
			m_pPlayer->Power(power);
		}
		if (PowerUpIsInLine(pu, l)) {
			m_pPowerUp.erase(m_pPowerUp.begin() + CVector::getVectorIndex(m_pPowerUp, pu));
		}
	}

	if (remainingPower <= 0) {
		power = false;
		remainingPower = 10;
		m_pPlayer->Power(power);
	}
}

void CGame::ChangeEnemySpeed()
{
	for (CEnemy* e : m_pEnemies)
	{
		e->m_Speed = enemySpeed;
	}
}

bool CGame::EnemyIsInPlayer(CPlayer* _player, CEnemy* _enemy)
{
	float l1x;
	float l1y;
	float r1x;
	float r1y;

	if (power == true) {
		 l1x = (_player->CTriangle::m_PointA[0] + _player->m_Translation[0]);//Ax
		 l1y = (_player->CTriangle::m_PointA[1] + _player->m_Translation[1])-0.5;//Ay, unten -0.25, *3 = -1.125
		 r1x = _player->CTriangle::m_PointC[0] + _player->m_Translation[0];//Cx 
		 r1y = (_player->CTriangle::m_PointC[1] + _player->m_Translation[1])+0.5; //Cy 0.5       = 1.875
	}
	else {
		 l1x = (_player->CTriangle::m_PointA[0] + _player->m_Translation[0]);//Ax
		 l1y = (_player->CTriangle::m_PointA[1] + _player->m_Translation[1]);//Ay, unten -0.25, *3 = -1.125
		 r1x = _player->CTriangle::m_PointC[0] + _player->m_Translation[0];//Cx 
		 r1y = (_player->CTriangle::m_PointC[1] + _player->m_Translation[1]); //Cy 0.5       = 1.875
	}
		
	//std::cout <<"!!!lix:" << l1x << " liy: " << l1y << " r1x: " << r1x << " r1y: " << r1y<<"\n";

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

bool CGame::PlayerIsInPowerUp(CPlayer* _player,CPowerUp* _powerUp) {

	 float l1x = _player->CTriangle::m_PointA[0] + _player->m_Translation[0];//Ax
	 float l1y = _player->CTriangle::m_PointA[1] + _player->m_Translation[1];//Ay
	 float r1x = _player->CTriangle::m_PointC[0] + _player->m_Translation[0];//Cx
	 float r1y = _player->CTriangle::m_PointC[1] + _player->m_Translation[1];//Cy
	

	float l2x = _powerUp->CTriangle::m_PointA[0] + _powerUp->m_Translation[0];//Ax
	float l2y = _powerUp->CTriangle::m_PointA[1] + _powerUp->m_Translation[1];//Ay
	float r2x = _powerUp->CTriangle::m_PointC[0] + _powerUp->m_Translation[0];//Cx
	float r2y = _powerUp->CTriangle::m_PointC[1] + _powerUp->m_Translation[1];//Cy

	if ((l1x >= l2x && r1x <= r2x) && ((l2y >= l1y && l2y <= r1y) || (r2y >= l1y && r2y <= r1y)))
		return true;

	return false;
}

bool CGame::PowerUpIsInLine(CPowerUp* _powerUp, CLeftLine* _leftLine) {

	float l1x = _powerUp->CTriangle::m_PointA[0] + _powerUp->m_Translation[0];//Ax
	float l1y = _powerUp->CTriangle::m_PointA[1] + _powerUp->m_Translation[1];//Ay
	float r1x = _powerUp->CTriangle::m_PointC[0] + _powerUp->m_Translation[0];//Cx
	float r1y = _powerUp->CTriangle::m_PointC[1] + _powerUp->m_Translation[1];//Cy

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