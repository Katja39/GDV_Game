#pragma once
#include "CTriangle.h"
#include "KeyState.h"

enum class EPlayerMoveState{UP,DOWN};

class CPlayer:public CTriangle {

private:
    static constexpr float m_PointA[3] = { -0.5, -0.5f, 0.0f };
    static constexpr float m_PointB[3] = { 2.0f, 0.3f, 0.0f };
    static constexpr float m_PointC[3] = { -0.5f,  1.0f, 0.0f };
    static constexpr float m_Color[4] = { 1.0f,  1.0f, 0.0f , 1.0f };
    float speed;

public:
    CPlayer();
    ~CPlayer();
    void OnUpdate(KeyState* _KeyState);
    bool PlayerIsAlive;
private:
    void Move(EPlayerMoveState _State);
};
