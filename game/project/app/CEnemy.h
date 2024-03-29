#pragma once
#include "CRectangle.h"

class CEnemy :public CRectangle {

    private:
        static constexpr float m_PointA[3] = { -0.25f, -0.25f, 0.0f };
        static constexpr float m_PointB[3] = { 0.25f, -0.25f, 0.0f };
        static constexpr float m_PointC[3] = { 0.25f,  0.25f, 0.0f };
        static constexpr float m_PointD[3] = { -0.25f,  0.25f, 0.0f };
        static constexpr float m_Color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };//red
        float m_speed = 0.02f;
    
    public:
        CEnemy(float _X, float _Y);
        ~CEnemy();
        void OnUpdate();
};
