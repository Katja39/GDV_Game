#pragma once
#include "CEnemy.h"
#include "CPowerUp.h"
#include <vector>

class CVector {
	public:
		static int getVectorIndex(std::vector<CEnemy*> v, CEnemy * K);
		static int getVectorIndex(std::vector<CPowerUp*> v, CPowerUp* K);
	};