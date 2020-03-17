// RANSAC.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include "iostream"
#include "RANSAC.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	std::cout << "Hello World!" << "\n";

	std::pair <double, double> myPair;
	std::vector <std::pair<double, double>> inputCloud;

	
	//reta y = -23x + 7
	int localCounter = 0;
	double X, Y;
	for (localCounter = 0; localCounter < 400; localCounter++) {
		X = (double)rand() / (double)RAND_MAX;
		Y = 7 * X + 25;
		inputCloud.push_back(std::make_pair(X, Y));
	}

	// lixo
	double rngX, rngY;
	for (localCounter = 0; localCounter < 1500; localCounter++) {
		rngX = 50 * (double)rand() / (double)RAND_MAX - 11;
		rngY = 70 * (double)rand() / (double)RAND_MAX - 31;
		inputCloud.push_back(std::make_pair(rngX, rngY));
	}
	
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
	myPair = myRansac.getLinearCoefficients(inputCloud, 1000, 0.2);
	//std::cout << "a: " << myPair.first << "\nb:  " << myPair.second << "\nare the coefficients of the linear curve!" << "\n";
	std::cout << "End! \n";
	
	getchar();
	return 0;
}

