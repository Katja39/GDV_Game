#pragma once

#include "yoshix_fix_function.h"
#include <vector>
#include "CPlayer.h"
#include "KeyState.h"

enum class EGameState { /*START,*/ RUN /*PAUSED,*/ /*GAMEOVER*/ };

class CGame {
    CGame(gfx::BHandle* _ppPlayerMesh);
    ~CGame();

    void InitGame();
    void RunGame(KeyState* _KeyState);
    //  void FinalizedGame();

public:
    gfx::BHandle* _ppPlayerMesh;
    CPlayer* _pPlayer;
};
