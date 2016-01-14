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

#include "../src/FileLayer.h"

using namespace std;
using namespace dwl;

int main()
{
	FileLayer* fh = new FileLayer();
	
	string cwdPath = fh->getCWD();
	string appPath = fh->getApplicationPath();
	
	cout << "CWD: " << cwdPath << endl;
	cout << "Application path: " << appPath << endl;

	string cur = fh->getCurrentPath();

	cout << "Current path " << cur << endl;

	cout << "DIRECTORY LISTING\n ---------------" << endl;
	vector<FileListing>* files = fh->getDirectoryListing();
	for (int i = 0; i < files->size(); i++)
	{
		FileListing file = files->at(i);
		if (file.isDirectory)
		{
			cout << "| " << file.FullName << " -DIR" << endl;
		}
		else
		{
			cout << "| " << file.FullName << endl;
		}
	}
	cout << " ---------------" << endl;

	fh->setCurrentPath("..\\");
	cur = fh->getCurrentPath();
	cout << "Current path NOW " << cur << endl;
	//cout << fh->isPathValid() << endl;
	
	cout << "DIRECTORY LISTING\n ---------------" << endl;
	files = fh->getDirectoryListing();
	for (int i = 0; i < files->size(); i++)
	{
		FileListing file = files->at(i);
		if (file.isDirectory)
		{
			cout << "| " << file.FullName << " -DIR" << endl;
		}
		else
		{
			cout << "| " << file.FullName << endl;
		}
	}
	cout << " ---------------" << endl;

	fh->setCurrentPath("C:\\dwl\\lab");
	cur = fh->getCurrentPath();
	cout << "Current path even later " << cur << endl;
	//cout << fh->isPathValid() << endl;

	cout << "DIRECTORY LISTING\n ---------------" << endl;
	files = fh->getDirectoryListing();
	for (int i = 0; i < files->size(); i++)
	{
		FileListing file = files->at(i);
		if (file.isDirectory)
		{
			cout << "| " << file.FullName << " -DIR" << endl;
		}
		else
		{
			cout << "| " << file.FullName << endl;
		}
	}
	cout << " ---------------" << endl;
	return 0;
}
