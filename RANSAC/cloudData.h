#pragma once

#include <vector>
#include <utility>

class cloudData
{
public:
	cloudData();
	~cloudData();

	std::vector <std::pair<double, double>> generateRandomCloud(int cloudSize, int boxSize);
	std::vector <std::pair<double, double>> generateFuzzyLinearCurve(double angularCoefficient, double linearCoefficient, int size, int fuzzyness);

};

