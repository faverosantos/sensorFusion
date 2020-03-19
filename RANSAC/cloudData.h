#pragma once

#include "myDefines.h"

class cloudData
{
public:
	cloudData();
	~cloudData();

	cloud dataPoints;
	
	void generateRandomCloud(int cloudSize, int boxSize);
	void generateFuzzyLinearCurve(double angularCoefficient, double linearCoefficient, int boxSize, int fuzzyness);

};

