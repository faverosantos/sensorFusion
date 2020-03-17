#include "stdafx.h"
#include "cloudData.h"


cloudData::cloudData()
{
}


cloudData::~cloudData()
{
}


// Creates a random data cloud inside the (-100,-100) to (100, 100) box
std::vector <std::pair<double, double>> cloudData::generateRandomCloud(int cloudSize, int boxSize) {
	
	std::vector <std::pair<double, double>> randonCloud;
	double rngX, rngY;
	int localCounter = 0;
	
	for (localCounter = 0; localCounter < cloudSize; localCounter++) {
		rngX = boxSize * (double)rand() / (double)RAND_MAX - boxSize/2;
		rngY = boxSize * (double)rand() / (double)RAND_MAX - boxSize/2;
		randonCloud.push_back(std::make_pair(rngX, rngY));
	}
	return randonCloud;
}

// Creates a fuzzy linear function curve
std::vector <std::pair<double, double>> cloudData::generateFuzzyLinearCurve(double angularCoefficient, double linearCoefficient, int size, int fuzzyness) {
	
	std::vector <std::pair<double, double>> fuzzyLinear;
	double X, Y;

	int localCounter = 0;

	for (localCounter = 0; localCounter < size; localCounter++) {
		X = 100 * (double)rand() / (double)RAND_MAX - 50;
		Y = X * angularCoefficient + linearCoefficient + fuzzyness*(double)rand() / (double)RAND_MAX - fuzzyness/2;
		fuzzyLinear.push_back(std::make_pair(X, Y));
	}
	return fuzzyLinear;
}
