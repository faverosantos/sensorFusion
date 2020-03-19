#include "stdafx.h"
#include "fileIO.h"

#include <iostream>
#include <fstream>
using namespace std;


fileIO::fileIO()
{
}


fileIO::~fileIO()
{
}

bool fileIO::save2file(std::vector<std::pair<double, double>> inputData, std::string fileName) {
	ofstream myfile(fileName);
	
	if (myfile.is_open()){

		int counter = 0;
		for (counter = 0; counter < inputData.size(); counter++) {
			myfile << inputData[counter].first << "  " << inputData[counter].second << "\n";
		}
		myfile.close();
		std::cout << "File written and closed." << endl;
		return true;
	}
	else {
		std::cout << "Unable to opern file." << endl;
		return false;
	}

}