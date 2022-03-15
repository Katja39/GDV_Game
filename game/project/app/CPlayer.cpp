#include "CPlayer.h"

CPlayer::CPlayer()
    :CTriangle((float*)PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_Color)
    ,PlayerIsAlive(true)
{
    speed = 0.1;
}

CPlayer::~CPlayer()
{
}

void CPlayer::OnUpdate(KeyState* _KeyState)
{
    if (_KeyState->isWdown) {
        Move(EPlayerMoveState::UP);
    }
    if (_KeyState->isSdown) {
        Move(EPlayerMoveState::DOWN);
    }
    fillVertices();
}

void CPlayer::Move(EPlayerMoveState _State)
{
  
}
