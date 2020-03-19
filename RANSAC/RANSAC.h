#pragma once
#include "myDefines.h"


class RANSAC
{
public:
	RANSAC();
	~RANSAC();

	std::pair <double, double> getLinearCoefficients(cloud inputCloud, int numberTries, double minimumDistance);
private:
	
};

