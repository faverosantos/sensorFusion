#pragma once
#include <utility>
#include <vector>


class RANSAC
{
public:
	RANSAC();
	~RANSAC();

	std::pair <double, double> getLinearCoefficients(std::vector <std::pair<double, double>> inputCloud, int numberTries, double minimumDistance);
private:
	
};

