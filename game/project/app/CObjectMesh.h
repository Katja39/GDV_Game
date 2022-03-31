#pragma once
#include "yoshix_fix_function.h"

class CObjectMesh {
	public:
		float m_Speed = 0;
		float m_Translation[3] = { 0, 0, 0 };
		float m_Scale[3] = { 1, 1, 1 };
		float m_Rotation[3] = { 0, 0, 0 };

	public: 
		CObjectMesh();
		~CObjectMesh();
		virtual gfx::SMeshInfo getMeshInfo() = 0;
};