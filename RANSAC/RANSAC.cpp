#include "stdafx.h"
#include "RANSAC.h"
#include <iostream>
#include "myDefines.h"


RANSAC::RANSAC()
{
}


RANSAC::~RANSAC()
{
}


std::unordered_set<int> RANSAC::returnInliers(cloud inputCloud, int numberTries, double minimumDistance) {
	
	std::unordered_set<int> inliersResult;
	std::unordered_set<int> inliersVolatile;
	srand(time(NULL));

	// Determines if a 2D or 3D RANSAC
	int counter = 0, dimension = 0;
	float sum = 0;

	for (counter = 0; counter < (int)inputCloud.size(); counter++) {
		sum = sum + std::get<2>(inputCloud[counter]);
	}

	if (sum > 0) {
		dimension = 3;
	}
	else {
		dimension = 2;
	}

	// For max iterations
	int i = 0, maximumInliers = 0, kick = 0;
	double x1 = 0, x2 = 0, x3 = 0, y1 = 0, y2 = 0, y3 = 0, z1 = 0, z2 = 0, z3 = 0;
	for (i = 0; i < numberTries; i++) {

		// Randomly sample subset and fit line
		inliersVolatile.clear();

		// Get random samples
		while ((int)inliersVolatile.size() < dimension) {
			kick = rand() % inputCloud.size();
			inliersVolatile.insert(kick);
		}

		// First random sample
		auto it = inliersVolatile.begin();
		double x1 = std::get<0>(inputCloud[*it]);
		double y1 = std::get<1>(inputCloud[*it]);
		double z1 = std::get<2>(inputCloud[*it]);
		it++;

		// Second random sample
		double x2 = std::get<0>(inputCloud[*it]);
		double y2 = std::get<1>(inputCloud[*it]);
		double z2 = std::get<2>(inputCloud[*it]);
		it++;

		if (dimension == 3) {
			// Third random sample
			double x3 = std::get<0>(inputCloud[*it]);
			double y3 = std::get<1>(inputCloud[*it]);
			double z3 = std::get<2>(inputCloud[*it]);
		}

		// Measure distance between every point and fitted line
		int iCloud = 0, inlierCounter = 0;
		double A = 0, B = 0, C = 0, D = 0, d = 0, x = 0, y = 0, z = 0;

		for (iCloud = 0; iCloud < (int)inputCloud.size(); iCloud++) {

			if (inliersVolatile.count(iCloud) > 0) {
				continue;
			}

			x = std::get<0>(inputCloud[iCloud]);
			y = std::get<1>(inputCloud[iCloud]);

			if (dimension == 3) {
				z = std::get<2>(inputCloud[iCloud]);

				A = (y2 - y1)*(z3 - z1) - (z2 - z1)*(y3 - y1);
				B = (z2 - z1)*(x3 - x1) - (x2 - x1)*(z3 - z1);
				C = (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);
				D = -(A * x1 + B * y1 + C * z1);
				d = fabs(A * x + B * y + C * z + D) / sqrt(pow(A, 2) + pow(B, 2) + pow(C, 2));

			}
			else if (dimension == 2) {

				A = y1 - y2;
				B = x2 - x1;
				C = x1 * y2 - x2 * y1;
				d = fabs(A * x + B * y + C) / sqrt(pow(A, 2) + pow(B, 2));
			}

			// If distance is smaller than threshold count it as inlier
			if (d <= minimumDistance) {
				inlierCounter++;
				inliersVolatile.insert(iCloud);
			}
		}

		if (inlierCounter > maximumInliers) {
			maximumInliers = inlierCounter;
			inlierCounter = 0;
			inliersResult = inliersVolatile;
		}

	}

	// Return indicies of inliers from fitted line with most inliers
	return inliersResult;
}

/*
Description: getLinearCoefficientsMethod0 uses two point samples to determine a linear function (LF). A third random point sample (P) is taken and the distance between P and the LF is determined.
If the calculated distance is lower than a threshold, a counter is updated. The highest number of counts implies in the highest propability of that LF being the best suited function to fit the data.
*/
/*std::pair <double, double> RANSAC::getLinearCoefficientsMethod0(cloud inputCloud, int numberTries, double minimumDistance) {

	int maximumHitCounter = 0;

	std::pair <double, double> returnCoefficients;

	int counterTries = 0;
	std::pair <double, double> firstPair, secondPair;

	for (counterTries = 0; counterTries < numberTries; counterTries++) {

		// 1. Take two random pairs of the inputCloud
		int kick = rand() % inputCloud.size();
		firstPair.first = inputCloud[kick].first; // x
		firstPair.second = inputCloud[kick].second; // y

		kick = rand() % inputCloud.size();
		secondPair.first = inputCloud[kick].first; //x
		secondPair.second = inputCloud[kick].second; // y

		// 2. Determine linear fitting function
		double a = (secondPair.second - firstPair.second) / (secondPair.first - firstPair.first);
		double b = secondPair.second - a * secondPair.first;

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
			double h = HP * sin(teta);

			// 4. Counter number of detected minimum distances
			if (abs(h) <= minimumDistance) {
				hitCounter++;
			}

			if (hitCounter > maximumHitCounter) {
				maximumHitCounter = hitCounter;
				returnCoefficients.first = a;
				returnCoefficients.second = b;
				//std::cout << "Minimum found at " << counterTries << " with " << hitCounter << " hits. Coefs are: a: " << a << " b: " << b << "\n";
			}
		}

		// 5. Repeat process until number of tries is achieved
	}
	std::cout << "Found coefficients are: a: " << returnCoefficients.first << " b: " << returnCoefficients.second << "\n";
	return returnCoefficients;
}*/

/*
Description: getLinearCoefficientsMethod1 uses a subset of the sample set and fits a linear function (LF) to that. The LF with the lowest error (distances inside that subset) is the best fitted LF for the data.
*/
/*std::pair <double, double> RANSAC::getLinearCoefficientsMethod1(cloud inputCloud, int numberTries, double minimumDistance, int subsetsNumber) {

	int maximumHitCounter = 0;

	std::pair <double, double> returnCoefficients;

	int counterTries = 0;
	std::pair <double, double> firstPair, secondPair, subsetPair;
	
	cloud subsetCloud;
	int subsetSize = 0;
	subsetSize = inputCloud.size() / subsetsNumber;

	for (counterTries = 0; counterTries < numberTries; counterTries++) {

		int subsetCounter = 0;
		for (subsetCounter = 0; subsetCounter < subsetsNumber; subsetCounter++) {
			
			// 0. Generates a random subsetCloud with a subsetSize size
			int localCounter = 0, kick = 0;
			for (localCounter = 0; localCounter < subsetSize; localCounter++) {
				kick = rand() % inputCloud.size();
				subsetPair.first = inputCloud[kick].first;
				subsetPair.second = inputCloud[kick].second;
				subsetCloud.push_back(subsetPair);
			}

			// 1. Take two random pairs of the subsetCloud
			kick = rand() % subsetCloud.size();
			firstPair.first = subsetCloud[kick].first; // x
			firstPair.second = subsetCloud[kick].second; // y

			kick = rand() % subsetCloud.size();
			secondPair.first = subsetCloud[kick].first; //x
			secondPair.second = subsetCloud[kick].second; // y*

			// 2. Determine linear fitting function for the subsetCloud
			double a = (secondPair.second - firstPair.second) / (secondPair.first - firstPair.first);
			double b = secondPair.second - a * secondPair.first;

			int local_counter = 0, hitCounter = 0;
			std::pair <double, double> pointValue;

			for (local_counter = 0; local_counter < subsetCloud.size(); local_counter++) {

				// 3. Iterate all values determining minimum distance between point and linear function
				// 3.1. Get a randon value, except actual values
				kick = rand() % subsetCloud.size();
				pointValue.first = subsetCloud[kick].first; // xp
				pointValue.second = subsetCloud[kick].second; // yp 

				// 3.2. Determine inclination of linear function
				double alfa = a;
				// 3.3. Determine beta
				double beta = (pointValue.second - firstPair.second) / (pointValue.first - firstPair.first);
				// 3.4. Determine teta
				double teta = beta - alfa;
				// 3.5 Determine HP
				double HP = sqrt(pow(pointValue.second - firstPair.second, 2) - pow(pointValue.first - firstPair.first, 2));
				// 3.6 Determine h
				double h = HP * sin(teta);

				// 4. Counter number of detected minimum distances
				if (abs(h) <= minimumDistance) {
					hitCounter++;
				}

				if (hitCounter > maximumHitCounter) {
					maximumHitCounter = hitCounter;
					returnCoefficients.first = a;
					returnCoefficients.second = b;
					//std::cout << "Minimum found at " << counterTries << " with " << hitCounter << " hits. Coefs are: a: " << a << " b: " << b << "\n";
				}
			}
		}

		// 5. Repeat process until number of tries is achieved
	}
	std::cout << "Found coefficients are: a: " << returnCoefficients.first << " b: " << returnCoefficients.second << "\n";
	return returnCoefficients;
}*/

/*
Description: getLinearCoefficientsMethod1 uses a subset of the sample set and fits a linear function (LF) to that. The LF with the lowest error (distances inside that subset) is the best fitted LF for the data.
*/
/*std::pair <double, double> RANSAC::getLinearCoefficientsMethod2(cloud inputCloud, int numberTries, double minimumDistance, int subsetsNumber) {
	std::unordered_set<int> inliersResult;
	std::unordered_set<int> inliersVolatile;
	srand(time(NULL));

	// TODO: Fill in this function

	// For max iterations
	int i = 0, maximumInliers = 0, kick = 0;
	for (i = 0; i < maxIterations; i++){

	  // Randomly sample subset and fit line
	  // First random sample
	  kick = rand() % cloud->size();
	  double x1 = (cloud->at(kick)).x;
	  double y1 = (cloud->at(kick)).y;

	  // Second random sample
	  kick = rand() % cloud->size();
	  double x2 = (cloud->at(kick)).x;
	  double y2 = (cloud->at(kick)).y;

	  // Measure distance between every point and fitted line
	  int iCloud = 0, inlierCounter = 0;
	  double A = 0, B = 0, C = 0, d = 0, x = 0, y = 0;

	  inliersVolatile.clear();
	  for(iCloud = 0; iCloud <  cloud->size(); iCloud++){

		x = (cloud->at(iCloud)).x;
		y = (cloud->at(iCloud)).y;
		A = y1 - y2;
		B = x2 - x1;
		C = x1 * y2 - x2 * y1;
		d = abs(A * x + B * y + C)/sqrt(pow(A,2) + pow(B,2));

		// If distance is smaller than threshold count it as inlier
		if (d <= distanceTol){
		  inlierCounter++;
		  inliersVolatile.insert(iCloud);
		}

		if (inlierCounter > maximumInliers){
			maximumInliers = inlierCounter;
			inlierCounter = 0;
			inliersResult.swap(inliersVolatile);
		}
	  }
	}

	// Return indicies of inliers from fitted line with most inliers
	return inliersResult;



}*/


/*
Solução UDACITY

std::unordered_set<int> Ransac(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, int maxIterations, float distanceTol){
	auto startTime = std::chrono::steady_clock::now();

	std::unordered_set<int> inliersResult;
	srand(time(NULL));


	while(maxIterations--){
		std::unordered_set<int> inliers;
		while (inliers.size() < 2){
			inliers.insert(radn()%(cloud->points.size()));
			// Isso é bem inteligente pq ele parte do pressuposto que os dois inliers chute fazem parte da reta
		}

		float x1, y1, x2, y2;
		// Isso retorna um ponteiro para o início da lista
		auto itr = inliers.begin();
		x1 = cloud->points[*itr].x;
		y1 = cloud->points[*itr].y;
		itr++;
		x2 = cloud->points[*itr].x;
		y2 = cloud->points[*itr].y;

		float a = (y1-y2);
		float b = (x2-x1);
		float c = (x1*y2 - x2*y1);

		for(int index = 0; index < cloud->points.size(); index++){
			if(inliers.count(index)>0)
				continue;

			pcl::PointXYZ point = cloud->points[index];
			float x3 = point.x;
			float y3 = point.y;

			float d = fabs(a*x3+b*y3+c)/sqrt(a*a+b*b);

			if (d <= distanceTol)
				inliers.insert(index);
		}

		if(inliers.size()>inliersResult.size()){
			inliersResult = inliers
		}
	}
	auto endTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime)
	std:;cout << "Ransac took " << elapsedTime.count() << " milliseconds" << std::endl;

	return inliersResults;
}


*/