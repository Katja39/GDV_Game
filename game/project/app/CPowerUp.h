#pragma once
#include "CTriangle.h"

class CPowerUp :public CTriangle {
	private:
        static constexpr float m_PointA[3] = { -0.3f, -0.3f, 0.0f };
        static constexpr float m_PointB[3] = { 0.3f, -0.3f, 0.0f };
        static constexpr float m_PointC[3] = { 0.0f,  0.0f, 0.0f };
        static constexpr float m_Color[4] = { 1.0f,  1.0f, 0.0f , 1.0f };//yellow

    public:
        CPowerUp(float _X, float _Y);
        ~CPowerUp();
        void OnUpdate();
};