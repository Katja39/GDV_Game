#pragma once

#include "yoshix_fix_function.h"
#include <vector>

#include "CPlayer.h"
#include "CEnemy.h"

#include "KeyState.h"

enum class EGameState { START, RUN, /*PAUSED,*/ /*GAMEOVER,*/ };
class CGame {
public:
    CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppEnemyMesh);
    ~CGame();

    void InitGame();
    void RunGame(KeyState* _KeyState);
    //void FinalizedGame();

private:
    void CreateEnemy();

    void EnemyAction();

    int m_Speed = 0;
    int m_MaxSpeedInterval = 10;
    int m_Ticks = 0;
    int m_MaxTicks = 80;
    

public:
    EGameState m_State;

    gfx::BHandle* m_ppPlayerMesh;
    gfx::BHandle* m_ppEnemyMesh;

    CPlayer* m_pPlayer;
    std::vector<CEnemy*> m_pEnemies;
};
