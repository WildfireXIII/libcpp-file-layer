//*************************************************************
//  File: Testing.cpp
//  Date created: 1/13/2016
//  Date edited: 1/13/2016
//  Author: Nathan Martindale
//  Copyright © 2016 Digital Warrior Labs
//  Description: 
//*************************************************************

#include <iostream>
#include <string>

#include "../src/FileHandler.h"

using namespace std;
using namespace dwl;

int main()
{
	FileHandler* fh = new FileHandler();
	
	string cwdPath = fh->getCWD();
	string appPath = fh->getApplicationPath();
	
	cout << "Current path: " << cwdPath << endl;
	cout << "Application path: " << appPath << endl;
	

	return 0;
}
