//*************************************************************
//  File: FileHandler.cpp
//  Date created: 1/13/2016
//  Date edited: 1/14/2016
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
	// private functions
	#ifdef _WIN32
		FileListing FileHandler::getFileListing(WIN32_FIND_DATA data)
		{
			FileListing file;
			file.Name = data.cFileName;
			file.FullName = m_currentPath + "\\" + data.cFileName;
		}
	#endif // _WIN32




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

	string FileHandler::getCurrentPath() { return m_currentPath; }
	void FileHandler::setCurrentPath(string path) 
	{ 
		#ifdef _WIN32
			char* currentPath = (char*)path.c_str();
			char newPath[MAX_PATH];

			// check that valid path (and resolve if relative path was passed
			if (_fullpath(newPath, currentPath, MAX_PATH) == NULL) { throw FileHandlerPathNotFound(); }

			string finalPath(newPath);
			m_currentPath = finalPath;
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux
	}

	/*bool FileHandler::isPathValid()
	{
		#ifdef _WIN32
			bool exists = PathFileExists(m_currentPath);
			return exists;
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux

		return false;
	}*/
	
	// TODO: overload, have an option to specify dirlisting of any path
	vector<FileListing>* FileHandler::getDirectoryListing()
	{
		vector<FileListing>* list = new vector<FileListing>();
		
		#ifdef _WIN32
			WIN32_FIND_DATA FindFileData;
			HANDLE hFind;

			hFind = FindFirstFile(m_currentPath + "\\*.*", &FindFileData);
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux
	}
}

#endif // FILE_HANDLER_CPP
