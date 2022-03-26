#pragma once
#include "CRectangle.h"

class CLeftLine :public CRectangle {

private:
	static constexpr float m_PointA[3] = { -0.05f,-9.0f / 2, 0 };
	static constexpr float m_PointB[3] = { 0.05f, -9.0f / 2, 0 };
	static constexpr float m_PointC[3] = { 0.05f, 9.0f / 2, 0 };
	static constexpr float m_PointD[3] = { -0.05f, 9.0f / 2, 0 };
	static constexpr float m_Color[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

public:
	CLeftLine();
	~CLeftLine();
};