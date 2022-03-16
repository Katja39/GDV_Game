#pragma once

#include "yoshix_fix_function.h"
#include <vector>

#include "CPlayer.h"
#include "CEnemy.h"
#include "KeyState.h"

enum class EGameState { START, RUN, /*PAUSED,*/ /*GAMEOVER,*/ };
class CGame {
public:
    CGame(gfx::BHandle* _ppPlayerMesh);
    ~CGame();

    void InitGame();
    void RunGame(KeyState* _KeyState);
    //void FinalizedGame();

private:

private:


public:
    EGameState m_State;

    gfx::BHandle* m_ppPlayerMesh;

    CPlayer* m_pPlayer;

};
