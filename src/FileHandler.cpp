//*************************************************************
//  File: FileHandler.cpp
//  Date created: 1/13/2016
//  Date edited: 1/13/2016
//  Author: Nathan Martindale
//  Copyright © 2016 Digital Warrior Labs
//  Description: Cross-platform file handling library
//*************************************************************

#ifndef FILE_HANDLER_CPP
#define FILE_HANDLER_CPP

#include "FileHandler.h"

using namespace std;

namespace dwl
{
	// construction
	FileHandler::FileHandler() 
	{ 
		m_currentPath = "";
		m_currentPath = this->getCWD();
	}
	FileHandler::~FileHandler() { }

	// path/directory stuff
	string FileHandler::getCWD()
	{
		#ifdef _WIN32
			char curDir[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, curDir);
			string path(curDir);
			return path;
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux

		return "";
	}

	string FileHandler::getApplicationPath()
	{
		#ifdef _WIN32
			char appPath[MAX_PATH];
			GetModuleFileName(NULL, appPath, MAX_PATH); // NULL means that it uses current executable
			
			// take of the executable name and just use path
			string path(appPath);
			int indexOfLast = path.find_last_of("/\\");
			path = path.substr(0, indexOfLast);
			return path;
		#endif // _WIN32

		#ifdef linux
		#endif // linux
		
		return "";
	}
	
}

#endif // FILE_HANDLER_CPP
