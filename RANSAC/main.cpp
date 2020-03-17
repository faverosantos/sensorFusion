// RANSAC.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "RANSAC.h"
#include "cloudData.h"



int main()
{
	std::cout << "Hello World!" << "\n";

	cloudData myCloudData;

	std::pair <double, double> myPair;
	std::vector <std::pair<double, double>> inputCloud, randomCloud;

	

	inputCloud = myCloudData.generateFuzzyLinearCurve(-2, 15, 200, 10);
	randomCloud = myCloudData.generateRandomCloud(1500, 500);
	inputCloud.insert(inputCloud.end(), randomCloud.begin(), randomCloud.end());

	//inputCloud.insert(inputCloud, myCloudData.generateRandomCloud(1500));
	// lixo
	/*double rngX, rngY;
	for (localCounter = 0; localCounter < 1500; localCounter++) {
		rngX = 200 * (double)rand() / (double)RAND_MAX - 100;
		rngY = 200 * (double)rand() / (double)RAND_MAX - 100;
		inputCloud.push_back(std::make_pair(rngX, rngY));
	}*/
	
	ofstream myfile("data.txt");
	if (myfile.is_open())
	{	
		int counter = 0;
		for (counter = 0; counter < inputCloud.size(); counter++) {
			myfile << inputCloud[counter].first << "  " << inputCloud[counter].second << "\n";
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	
	
	RANSAC myRansac;
	myPair = myRansac.getLinearCoefficients(inputCloud, 10000, 0.2);
	//std::cout << "a: " << myPair.first << "\nb:  " << myPair.second << "\nare the coefficients of the linear curve!" << "\n";*/
	std::cout << "End! \n";
	
	getchar();
	return 0;
}

