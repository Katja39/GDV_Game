#include "CLeftLine.h"

CLeftLine::CLeftLine()
	:CRectangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_PointD, (float*)m_Color)
{
	m_Translation[0] = -5.75f;
	m_Translation[1] = 0.0f;
}

CLeftLine::~CLeftLine()
{
}
