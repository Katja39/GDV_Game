#pragma once

#include "yoshix_fix_function.h"
#include <vector>

#include "CPlayer.h"
#include "CEnemy.h"
#include "CLeftLine.h"
#include "CPowerUp.h"

#include "KeyState.h"

enum class EGameState {START,RUN,GAMEOVER};
class CGame {
    public:
        CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppEnemyMesh,gfx::BHandle* _ppLeftLineMesh,gfx::BHandle* _ppPowerUpMesh);
        ~CGame();

        void InitGame();
        void RunGame(KeyState* _KeyState);
        void FinalizedGame();

    private:
        void CreateEnemy();
        void SpawnEnemy();
        void EnemyAction();
        void ChangeEnemySpeed();

        void CreatePowerUp();
        void SpawnPowerUp();
        void PowerUpAction();

        void CollisionControllEnemy();
        void CollisionControllPowerUp();

        bool EnemyIsInPlayer(CPlayer* _player, CEnemy* _enemy);
        bool EnemyIsInLine(CEnemy* _enemy, CLeftLine* _leftLine);
        bool PlayerIsInPowerUp(CPlayer* _player, CPowerUp* _powerUp);
        bool PowerUpIsInLine(CPowerUp* _powerUp, CLeftLine* _leftLine);

        int spawnNumberOfEnemies = 3;
        int score = 0;
        int round = 1;
        int level = 1;

        bool power = false;//true, if collect PowerUp
        int remainingPower = 10;

        float enemySpeed = 0.02;


    public:
        EGameState m_State;

        gfx::BHandle* m_ppPlayerMesh;
        gfx::BHandle* m_ppEnemyMesh;
        gfx::BHandle* m_ppPowerUpMesh;
        gfx::BHandle* m_ppLeftLineMesh;

        CPlayer* m_pPlayer;
        CLeftLine* m_pLeftLine;
    
        std::vector<CPowerUp*> m_pPowerUp;
        std::vector<CEnemy*> m_pEnemies;
};
