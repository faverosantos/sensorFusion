#pragma once

#include "myDefines.h"

class cloudData
{
public:
	cloudData();
	~cloudData();

	cloud dataPoints;
	
	void generateRandomCloud(int cloudSize, int boxSize, int dimension);
	void generateFuzzyLinearCurve(float angularCoefficient, float linearCoefficient, int boxSize, int fuzzyness);

};

