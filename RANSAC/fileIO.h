#pragma once
#include <string>
#include <utility>
#include <vector>

class fileIO
{
public:
	fileIO();	
	~fileIO();

	bool save2file(std::vector<std::pair<double, double>> inputData, std::string fileName);
};

