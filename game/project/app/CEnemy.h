#pragma once
#include "CRectangle.h"

enum class EMoveState { UP, DOWN, LEFT };
class CEnemy :public CRectangle {

private:
    static constexpr float m_PointA[3] = { -0.25f, -0.25f, 0.0f };
    static constexpr float m_PointB[3] = { 0.25f, -0.25f, 0.0f };
    static constexpr float m_PointC[3] = { 0.25f,  0.25f, 0.0f };
    static constexpr float m_PointD[3] = { -0.25f,  0.25f, 0.0f };
    static constexpr float m_Color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };


public:
    CEnemy(float _X, float _Y);
    ~CEnemy();
    void OnUpdate();
    float getPointA_X();
    EMoveState m_MoveState;

private:
    void Move(EMoveState _State);
};
