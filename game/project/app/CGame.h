#pragma once

#include "yoshix_fix_function.h"
#include <vector>

#include "CPlayer.h"
#include "CEnemy.h"
#include "CLeftLine.h"

#include "KeyState.h"

enum class EGameState {START,RUN,GAMEOVER};
class CGame {
public:
    CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppEnemyMesh,gfx::BHandle* _ppLeftLineMesh);
    ~CGame();

    void InitGame();
    void RunGame(KeyState* _KeyState);
    void FinalizedGame();

private:
    void CreateEnemy();
    void SpawnEnemy();
    void EnemyAction();

    void CollisionControll();
    bool EnemyIsInPlayer(CPlayer* _player, CEnemy* _enemy);
    bool EnemyIsInLine(CEnemy* _enemy, CLeftLine* _leftLine);

    //bool GameOver(CEnemy* _enemy);

    bool changeLevel=false; //true, wenn es aufgerufen wird
    int SpawnNumberOfEnemies = 4;
    int score = 0;
    int level = 1;

public:
    EGameState m_State;

    gfx::BHandle* m_ppPlayerMesh;
    gfx::BHandle* m_ppEnemyMesh;
    gfx::BHandle* m_ppLeftLineMesh;

    CPlayer* m_pPlayer;
    CLeftLine* m_pLeftLine;
    std::vector<CEnemy*> m_pEnemies;
};
