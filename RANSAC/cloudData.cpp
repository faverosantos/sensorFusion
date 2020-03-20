#include "stdafx.h"
#include "cloudData.h"


cloudData::cloudData(){
	this->dataPoints = {};
}


cloudData::~cloudData()
{
}

// Creates a 3D random data cloud inside the box of size boxSize
void cloudData::generateRandomCloud(int cloudSize, int boxSize, int dimension) {
	
	float rngX, rngY, rngZ;
	int localCounter = 0;
	
	for (localCounter = 0; localCounter < cloudSize; localCounter++) {
		rngX = boxSize * (float)rand() / (float)RAND_MAX - boxSize / 2;
		rngY = boxSize * (float)rand() / (float)RAND_MAX - boxSize / 2;
		rngZ = 0.0;
		if (dimension == 3) {
			rngZ = boxSize * (float)rand() / (float)RAND_MAX - boxSize / 2;
		}
		dataPoints.push_back(std::make_tuple(rngX, rngY, rngZ));
	}
}

// Creates a fuzzy linear function curve of boxSize 
void cloudData::generateFuzzyLinearCurve(float angularCoefficient, float linearCoefficient, int boxSize, int fuzzyness) {
	
	float X, Y;
	int localCounter = 0;

	for (localCounter = 0; localCounter < boxSize; localCounter++) {
		X = boxSize * (float)rand() / (float)RAND_MAX - boxSize/2;
		Y = X * angularCoefficient + linearCoefficient + fuzzyness*(float)rand() / (float)RAND_MAX - fuzzyness/2;
		dataPoints.push_back(std::make_tuple(X, Y, (float)0));
	}
}