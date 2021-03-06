//*************************************************************
//  File: FileLayer.cpp
//  Date created: 1/13/2016
//  Date edited: 2/19/2016
//  Author: Nathan Martindale
//  Copyright © 2016 Digital Warrior Labs
//  Description: Cross-platform file handling library
//*************************************************************

#ifndef FILE_LAYER_CPP
#define FILE_LAYER_CPP

#include "FileLayer.h"

using namespace std;

namespace dwl
{
	// private functions
	#ifdef _WIN32
		FileListing* FileLayer::getFileListing(WIN32_FIND_DATA data)
		{
			FileListing* file = new FileListing();
			string fullName(data.cFileName);
			int index = fullName.find_last_of(".");

			file->FullName = fullName;
			if (index != -1) 
			{ 
				file->Name = fullName.substr(0, index); 
				file->Extension = fullName.substr(index); // NOTE: includes .
			}
			else // either no extension or directory
			{ 
				file->Name = file->FullName; 
				file->Extension = "";
			}

			file->Path = m_currentPath;

			// check whether dir or not (checks if directory attribute flag set)
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { file->isDirectory = true; }
			else { file->isDirectory = false; }

			return file;
		}

		void FileLayer::recursiveDelDir(string path)
		{
			this->setCurrentPath(path);
			path = m_currentPath;
			vector<FileListing>* files = this->getDirectoryListing();
			if (files->size() > 2) // 2 to account for . and ..
			{
				for (int i = 2; i < files->size(); i++)
				{
					FileListing file = files->at(i);
					if (file.isDirectory) { this->recursiveDelDir(path + "\\" + file.FullName); }
					else { this->deleteFile(path + "\\" + file.FullName); }
				}
			}
			this->setCurrentPath(path + "\\..");
			RemoveDirectory(path.c_str());
		}
	#endif // _WIN32

	// construction
	FileLayer::FileLayer() 
	{ 
		m_currentPath = "";
		m_currentPath = this->getCWD();
	}
	FileLayer::~FileLayer() 
	{ 
		// clean up
		m_openFile.close();
	}

	ofstream* FileLayer::getOFStream() { return &m_openFile; }

	// path/directory stuff
	// TODO: PASS IN string of path where to write
	void FileLayer::outputCWD(string path)
	{
		#ifdef _WIN32
			//SetCurrentDirectory(m_currentPath.c_str()); // DOESN'T WORK OUT OF THE CURRENT INSTANCE

			// writes the path out to a file, can be read by a parent shell script
			this->quickWrite(this->getCurrentPath(), path + "\\_FILELAYER_CWD.dat", false);
			
			return;
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux
	}
	
	string FileLayer::getCWD()
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

	string FileLayer::getApplicationPath()
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

	string FileLayer::getCurrentPath() { return m_currentPath; }
	void FileLayer::setCurrentPath(string path) 
	{ 
		#ifdef _WIN32
			char* currentPath = (char*)path.c_str();
			char newPath[MAX_PATH];

			// check that valid path (and resolve if relative path was passed
			if (_fullpath(newPath, currentPath, MAX_PATH) == NULL) { throw FileLayerPathNotFound(); }

			string finalPath(newPath);
			m_currentPath = finalPath;

			if (!this->isDirectory(m_currentPath)) { throw FileLayerNotDirectory(); }
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux
	}

	bool FileLayer::isDirectory(string path)
	{
		#ifdef _WIN32
			DWORD attributes = GetFileAttributes(path.c_str());
			if (attributes == INVALID_FILE_ATTRIBUTES) { return false; }
			if (attributes & FILE_ATTRIBUTE_DIRECTORY) { return true; }
			return false;
		#endif // _WIN32

		#ifdef linux
		#endif // linux
	}
	
	bool FileLayer::isFile(string path)
	{
		#ifdef _WIN32
			DWORD attributes = GetFileAttributes(path.c_str());
			if (attributes == INVALID_FILE_ATTRIBUTES) { return false; }
			if (attributes & FILE_ATTRIBUTE_DIRECTORY) { return false; }
			return true;
		#endif // _WIN32

		#ifdef linux
		#endif // linux
	}
	
	bool FileLayer::exists(string path)
	{
		#ifdef _WIN32
			DWORD attributes = GetFileAttributes(path.c_str());
			if (attributes == INVALID_FILE_ATTRIBUTES) { return false; }
			return true;
		#endif // _WIN32

		#ifdef linux
		#endif // linux
	}

	// TODO: NEVER ANY TRAILING BACKSLASHES 
	
	vector<FileListing>* FileLayer::getDirectoryListing()
	{
		vector<FileListing>* list = new vector<FileListing>();
		
		#ifdef _WIN32
			WIN32_FIND_DATA FindFileData;
			HANDLE hFind;

			// define what to search for
			string strSearchPath = m_currentPath + "\\*.*";
			LPCSTR searchPath = strSearchPath.c_str();

			// get first file
			hFind = FindFirstFile(searchPath, &FindFileData);
			FileListing* firstFileListing = getFileListing(FindFileData);
			list->push_back(*firstFileListing);

			// list all the rest
			while (FindNextFile(hFind, &FindFileData))
			{
				FileListing* nextFileListing = getFileListing(FindFileData);
				list->push_back(*nextFileListing);
			}

			// clean up
			FindClose(hFind);
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux

		return list;
	}

	void FileLayer::createFile(string path)
	{
		ofstream file;
		file.open(path);
		file.close();
	}

	void FileLayer::createDirectory(string path)
	{
		#ifdef _WIN32
			CreateDirectory(path.c_str(), NULL);
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux
	}

	void FileLayer::deleteFile(string path) { remove(path.c_str()); }
	
	void FileLayer::deleteDirectory(string path)
	{
		#ifdef _WIN32
			recursiveDelDir(path);
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux
	}

	vector<string>* FileLayer::readFile(string fileName)
	{
		vector<string>* lines = new vector<string>();
		string line = "";
		ifstream fileStream(fileName);
		if (fileStream.is_open())
		{
			while (getline(fileStream, line)) { lines->push_back(line); }
		}
		fileStream.close();
		return lines;
	}

	void FileLayer::prepareFileWrite(string fileName, bool append)
	{
		// make sure any old files were closed
		m_openFile.close();
		
		if (append) { m_openFile = ofstream(fileName, ios::out | ios::app); }
		else { m_openFile = ofstream(fileName, ios::out); }
	}

	// NOTE: does not automatically add line endings!
	void FileLayer::fileWrite(string content)
	{
		if (m_openFile.is_open()) { m_openFile << content; }
	}

	void FileLayer::finishWrite() { m_openFile.close(); }

	void FileLayer::quickWrite(string content, string fileName, bool append)
	{
		ofstream fileStream;
		if (append) { fileStream.open(fileName, ios::out | ios::app); }
		else { fileStream.open(fileName, ios::out); }
		if (fileStream.is_open()) { fileStream << content; }
		fileStream.close();
	}
}

#endif // FILE_LAYER_CPP
