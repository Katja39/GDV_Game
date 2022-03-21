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
    float padding = 0.5f;
    double width = 12.0f; //window width
    double height = 9.0f; //window height

    switch (m_MoveState)
    {
    case EMoveState::DOWN: 
        if (m_Translation[1] <= -(height / 2) + padding) //bottom border
        {
            m_MoveState = EMoveState::LEFT;
            Move(m_MoveState);
            m_MoveState = EMoveState::UP;
        }
        else
        {
            Move(m_MoveState);
        }
        break;
    case EMoveState::UP:
        if (m_Translation[1] >= (12.0f/2) - padding) //Right Border
        {
            m_MoveState = EMoveState::LEFT;
            Move(m_MoveState);
            m_MoveState = EMoveState::DOWN;
        }
        else
        {
            Move(m_MoveState);
        }
        break;
    default:
        break;
    }
}

void CEnemy::Move(EMoveState _State)
{
    switch (_State)//TODO stimmt noch nicht
    {
    case EMoveState::LEFT:
        m_Translation[0] -= 0.5f;
        break;
    case EMoveState::UP:
        m_Translation[1] += 0.5f;
        break;
    case EMoveState::DOWN:
        m_Translation[1] -= 0.5f;
    default:
        break;
    }
}