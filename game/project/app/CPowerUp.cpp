#include "CPowerUp.h"

CPowerUp::CPowerUp(float _X, float _Y)
	:CTriangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_Color)
{
	m_Translation[0] = _X;
	m_Translation[1] = _Y;
}

CPowerUp::~CPowerUp()
{
}

void CPowerUp::OnUpdate()
{
	m_Translation[0] -= 0.02f;
	m_Rotation[2] += 4;
	fillVertices();
}
