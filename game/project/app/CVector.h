#pragma once
#include "CEnemy.h"
#include <vector>

class CVector {
	public:
		static int getVectorIndex(std::vector<CEnemy*> v, CEnemy * K);
	};