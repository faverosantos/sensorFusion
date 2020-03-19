// RANSAC.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include <iostream>

#include "myDefines.h"
#include "RANSAC.h"
#include "cloudData.h"
#include "fileIO.h"



int main(int argc, char** argv)
{
	std::cout << "Hello World!" << "\n";

	double angularCoef = atof(argv[1]);
	double linearCoef = atof(argv[2]);

	std::cout << angularCoef << "\n";
	std::cout << linearCoef << "\n";

	cloudData myCloudData;
	myCloudData.generateFuzzyLinearCurve(angularCoef, linearCoef, 500, 10);
	myCloudData.generateRandomCloud(0, 500);

	fileIO myFile;
	//myFile.save2file(myCloudData.dataPoints, "data.txt");
	
	RANSAC myRansac;
	std::pair <double, double> myPair;
	myPair = myRansac.getLinearCoefficients(myCloudData.dataPoints, 2000, 0.5);
	
	myCloudData.dataPoints.push_back(myPair);
	myFile.save2file(myCloudData.dataPoints, "data.txt");

	std::cout << "End! \n";
	//getchar();
	return 0;
}

