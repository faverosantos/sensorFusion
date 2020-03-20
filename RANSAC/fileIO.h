#pragma once
#include "myDefines.h"

class fileIO
{
public:
	fileIO();	
	~fileIO();

	bool save2file(cloud inputData, std::string fileName);
};

