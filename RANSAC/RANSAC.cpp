#include "stdafx.h"
#include "RANSAC.h"
#include <iostream>
#include "myDefines.h"
#include <vector>


RANSAC::RANSAC()
{
}


RANSAC::~RANSAC()
{
}

std::pair <double, double> RANSAC::getLinearCoefficients(std::vector <std::pair<double, double>> inputCloud, int numberTries, double minimumDistance) {

	
	int maximumHitCounter = 0;
	
	std::pair <double, double> returnCoefficients;
		
	int counterTries = 0;
	for (counterTries = 0; counterTries < numberTries; counterTries++){
		
		// 1. Take two random pairs and create return coefficients
		std::pair <double, double> firstPair, secondPair;
		
		int kick = rand() % inputCloud.size();
		firstPair.first = inputCloud[kick].first; // x
		firstPair.second = inputCloud[kick].second; // y

		kick = rand() % inputCloud.size();
		secondPair.first = inputCloud[kick].first; //x
		secondPair.second = inputCloud[kick].second; // y

		// 2. Determine linear fitting function
		double a = (secondPair.second - firstPair.second) / (secondPair.first - firstPair.first);
		double b = secondPair.second - a*secondPair.first;

		int local_counter = 0, hitCounter = 0;
		std::pair <double, double> pointValue;

		for (local_counter = 0; local_counter < inputCloud.size(); local_counter++) {

			// 3. Iterate all values determining minimum distance between point and linear function
			// 3.1. Get a randon value, except actual values
			kick = rand() % inputCloud.size();
			pointValue.first = inputCloud[kick].first; // xp
			pointValue.second = inputCloud[kick].second; // yp 

			// 3.2. Determine inclination of linear function
			double alfa = a;// *180 / PI;
			// 3.3. Determine beta
			double beta = (pointValue.second - firstPair.second) / (pointValue.first - firstPair.first);
			// 3.4. Determine teta
			double teta = beta - alfa;
			// 3.5 Determine HP
			double HP = sqrt(pow(pointValue.second - firstPair.second, 2) - pow(pointValue.first - firstPair.first, 2));
			// 3.6 Determine h
			double h = HP*sin(teta);

			// 4. Counter number of detected minimum distances
			if (abs(h) <= minimumDistance) {
				hitCounter++;
			}

			if (hitCounter > maximumHitCounter) {
				maximumHitCounter = hitCounter;
				returnCoefficients.first = a;
				returnCoefficients.second = b;
				std::cout << "Minimum found at " << counterTries << " with " << hitCounter << " hits. Coefs are: a: " << a << " b: " << b << "\n";
			}
		}

	// 5. Repeat process until number tries is achieved
	}

	return returnCoefficients;
}

