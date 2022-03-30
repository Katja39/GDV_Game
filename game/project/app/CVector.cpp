#include "CVector.h"
#include <iostream>

int CVector::getVectorIndex(std::vector<CEnemy*> v, CEnemy* K)
{
	auto it = find(v.begin(), v.end(), K);

	// If element was found
	if (it != v.end())
	{

		// calculating the index
		int index = it - v.begin();
		return index;
	}
	else {
		std::cout << "-1" << std::endl;
	}
}
int CVector::getVectorIndex(std::vector<CPowerUp*> v, CPowerUp* K)
{
	auto it = find(v.begin(), v.end(), K);

	// If element was found
	if (it != v.end())
	{

		// calculating the index
		int index = it - v.begin();
		return index;
	}
	else {
		std::cout << "-1" << std::endl;
	}
}