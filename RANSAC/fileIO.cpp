#include "stdafx.h"
#include "fileIO.h"
#include "myDefines.h"

#include <iostream>
#include <fstream>
using namespace std;


fileIO::fileIO()
{
}


fileIO::~fileIO()
{
}

bool fileIO::save2file(cloud inputData, std::string fileName) {
	ofstream myfile(fileName);
	
	//std::get<1>(myPoint);
	if (myfile.is_open()){

		int counter = 0;
		for (counter = 0; counter < (int)inputData.size(); counter++) {
			//myfile << inputData[counter].first << "  " << inputData[counter].second << " " << inputData[counter].second << "\n";
			myfile << std::get<0>(inputData[counter]) << "  " << std::get<1>(inputData[counter]) << " " << std::get<2>(inputData[counter]) << "\n"; 
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