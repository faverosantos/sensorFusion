#include "stdafx.h"
#include "cloudData.h"


cloudData::cloudData(){
	this->dataPoints = {};
}


cloudData::~cloudData()
{
}


// Creates a random data cloud inside the box of size boxSize
void cloudData::generateRandomCloud(int cloudSize, int boxSize) {
	
	double rngX, rngY;
	int localCounter = 0;
	
	for (localCounter = 0; localCounter < cloudSize; localCounter++) {
		rngX = boxSize * (double)rand() / (double)RAND_MAX - boxSize/2;
		rngY = boxSize * (double)rand() / (double)RAND_MAX - boxSize/2;
		dataPoints.push_back(std::make_pair(rngX, rngY));
	}
}

// Creates a fuzzy linear function curve of boxSize 
void cloudData::generateFuzzyLinearCurve(double angularCoefficient, double linearCoefficient, int boxSize, int fuzzyness) {
	
	double X, Y;
	int localCounter = 0;

	for (localCounter = 0; localCounter < boxSize; localCounter++) {
		X = boxSize * (double)rand() / (double)RAND_MAX - boxSize/2;
		Y = X * angularCoefficient + linearCoefficient + fuzzyness*(double)rand() / (double)RAND_MAX - fuzzyness/2;
		dataPoints.push_back(std::make_pair(X, Y));
	}
}
