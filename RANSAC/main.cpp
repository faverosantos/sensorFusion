// RANSAC.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include <iostream>
#include <unordered_set>

#include "myDefines.h"
#include "RANSAC.h"
#include "cloudData.h"
#include "fileIO.h"



int main(int argc, char** argv)
{
	std::cout << "Hello World!" << "\n";

	/*double angularCoef = atof(argv[1]);
	double linearCoef = atof(argv[2]);

	std::cout << "Inserted angular coefficient is: " <<angularCoef << "\n";
	std::cout << "Inserted linear coefficient is: " << linearCoef << "\n";*/
	
	float angularCoef = -3;
	float linearCoef = 5;

	cloudData myCloudData;
	myCloudData.generateFuzzyLinearCurve(angularCoef, linearCoef, 50, 5);
	myCloudData.generateRandomCloud(1000, 1000, 2);

	fileIO myFile;
	//myFile.save2file(myCloudData.dataPoints, "data.txt");
	
	RANSAC myRansac;
	//std::pair <double, double> myPairM0,myPairM1;
	std::unordered_set<int> inliers;
	inliers = myRansac.returnInliers(myCloudData.dataPoints, 100, 0.2);

	myFile.save2file(myCloudData.dataPoints, "data.txt");

	std::cout << "End! \n";
	//getchar();
	return 0;
}

