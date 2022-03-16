#include "CPlayer.h"
#include <math.h>

CPlayer::CPlayer()
    :CTriangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_Color)
    ,PlayerIsAlive(true)
{
    speed = 0.1;
    m_Translation[0] = -5.0f;
    m_Translation[1] = 0.0f;

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
    float* XPos = &m_Translation[0];
    float halfWidth = (fabsf((float)m_PointA[0]) + fabsf((float)m_PointB[0])) / 2;

    if (_State == EPlayerMoveState::UP)  *XPos -= m_Speed;
    if (_State == EPlayerMoveState::DOWN) *XPos += m_Speed;
}
