#include "CPlayer.h"
#include <math.h>

CPlayer::CPlayer()
    :CTriangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_Color)
{
    m_Speed = 0.2;
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
    if (_KeyState->isDdown) {
        Move(EPlayerMoveState::RIGHT);
    }
    if (_KeyState->isAdown) {
        Move(EPlayerMoveState::LEFT);
    }
    fillVertices();
}

void CPlayer::Power(bool _power)
{
    if (_power == true) {
        m_Scale[0] = 3;
        m_Scale[1] = 3;
    }
    else {
        m_Scale[0] = 1;
        m_Scale[1] = 1;
    }
  
}

void CPlayer::Move(EPlayerMoveState _State)
{
    float* XPos = &m_Translation[0];
    float* YPos = &m_Translation[1];
    float halfWidth = (fabsf((float)m_PointA[0]) + fabsf((float)m_PointB[0])) / 2;
      
    if (_State == EPlayerMoveState::DOWN)  *YPos -= m_Speed;
    if (_State == EPlayerMoveState::UP) *YPos += m_Speed;

    if (_State == EPlayerMoveState::LEFT) *XPos -= m_Speed;
    if (_State == EPlayerMoveState::RIGHT) *XPos += m_Speed;

    if (*YPos < -9.0f / 2 + halfWidth){ //bottom
        *YPos = -9.0f / 2 + halfWidth;
    }
   if (*YPos > 9.0f / 2 - halfWidth) { //top
        *YPos = 9.0f / 2 - halfWidth;
    }
   if (*XPos > 10.5f / 2 - halfWidth) { //right
       *XPos = 10.5f / 2 - halfWidth;
   }
   if (*XPos < -9.5f / 2 - halfWidth) { //left
       *XPos = -9.5f / 2 - halfWidth;
   }

}
