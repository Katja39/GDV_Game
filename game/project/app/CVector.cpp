#include "CVector.h"
#include <iostream>

int CVector::getVectorIndex(std::vector<CEnemy*> v, CEnemy* K)
{
	auto it = find(v.begin(), v.end(), K);

	if (it != v.end())
	{
		int index = it - v.begin();
		return index;
	}
}
int CVector::getVectorIndex(std::vector<CPowerUp*> v, CPowerUp* K)
{
	auto it = find(v.begin(), v.end(), K);

	if (it != v.end())
	{
		int index = it - v.begin();
		return index;
	}
}