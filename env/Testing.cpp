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

	fh->setCurrentPath(fh->getCWD());
	cout << "Current path: " << fh->getCurrentPath() << endl;
	cout << "blahblah.txt exists: " << fh->exists("blahblah.txt") << endl;
	cout << "Testing.exe exists: " << fh->exists("Testing.exe") << endl;
	cout << "Testing.exe is a directory: " << fh->isDirectory("Testing.exe") << endl;
	cout << "Testing.exe is a file: " << fh->isFile("Testing.exe") << endl;
	cout << "../src is a directory: " << fh->isDirectory("../src") << endl;
	cout << "/dwl is a directory: " << fh->isDirectory("/dwl") << endl;
	cout << "/dwl/laba exists: " << fh->exists("/dwl/laba") << endl;
	
	if (!fh->exists("TESTING.txt")) 
	{ 
		cout << "Creating file TESTING.txt" << endl; 
		fh->createFile("TESTING.txt");
	}
	if (!fh->exists("LOLDIR"))
	{
		cout << "Creating directory LOLDIR" << endl;
		fh->createDirectory("LOLDIR");
	}
	cout << "TESTING.txt exists: " << fh->exists("TESTING.txt") << endl;
	cout << "Deleting files..." << endl;
	fh->deleteFile("TESTING.txt");
	cout << "TESTING.txt exists: " << fh->exists("TESTING.txt") << endl;

	fh->deleteDirectory("LOLDIR");
	cout << "current: " << fh->getCurrentPath() << endl;
	
	return 0;
}
