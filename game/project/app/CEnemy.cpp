#include "CEnemy.h"


CEnemy::CEnemy(float _X, float _Y)
    : CRectangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_PointD, (float*)m_Color)
    , m_MoveState(EMoveState::DOWN)
{

    m_Translation[0] = _X;
    m_Translation[1] = _Y;
}

CEnemy::~CEnemy()
{
}

void CEnemy::OnUpdate()
{
    m_Translation[0] -= 0.03f;
}

float CEnemy::getPointA_X() //to detect if object in window
{
    return m_PointA[0];
}

void CEnemy::Move(EMoveState _State)
{ 
}
