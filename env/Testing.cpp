//*************************************************************
//  File: Testing.cpp
//  Date created: 1/13/2016
//  Date edited: 1/14/2016
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
	
	cout << "CWD: " << cwdPath << endl;
	cout << "Application path: " << appPath << endl;

	string cur = fh->getCurrentPath();

	cout << "Current path " << cur << endl;

	fh->setCurrentPath("..\\");
	cur = fh->getCurrentPath();
	cout << "Current path NOW " << cur << endl;
	//cout << fh->isPathValid() << endl;

	fh->setCurrentPath("C:\\dwl\\laba");
	cur = fh->getCurrentPath();
	cout << "Current path even later " << cur << endl;
	//cout << fh->isPathValid() << endl;
	

	return 0;
}
