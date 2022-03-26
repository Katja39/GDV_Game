#include "CPlayer.h"
#include <math.h>

CPlayer::CPlayer()
    :CTriangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_Color)
    ,PlayerIsAlive(true)
{
    m_Speed = 0.18;
    m_Translation[0] = -5.0f;
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
    float* YPos = &m_Translation[1];
    float halfWidth = (fabsf((float)m_PointA[0]) + fabsf((float)m_PointB[0])) / 2;

    if (_State == EPlayerMoveState::DOWN)  *YPos -= m_Speed;
    if (_State == EPlayerMoveState::UP) *YPos += m_Speed;

    if (*YPos < -9.0f / 2 + halfWidth){ //bottom
        *YPos = -9.0f / 2 + halfWidth;
    }
   if (*YPos > 9.0f / 2 - halfWidth) { //top
        *YPos = 9.0f / 2 - halfWidth;
    }

}
