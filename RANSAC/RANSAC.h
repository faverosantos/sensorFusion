#pragma once
#include "myDefines.h"


class RANSAC
{
public:
	RANSAC();
	~RANSAC();

	std::unordered_set<int> RANSAC::returnInliers(cloud inputCloud, int numberTries, double minimumDistance);
	/*std::pair <double, double> getLinearCoefficientsMethod0(cloud inputCloud, int numberTries, double minimumDistance);
	std::pair <double, double> getLinearCoefficientsMethod1(cloud inputCloud, int numberTries, double minimumDistance, int subsetSize);*/
private:
	
};

