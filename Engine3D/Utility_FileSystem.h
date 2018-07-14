#pragma once

#include <string>

/*
Set of useful methods for working with the file system
*/

// @return Folder from which the process was launched
std::string& Utility_FileSystem_GetExeFolder();

// Gets the absolute path of the current working directory
// NEED set the working directory first
// std :: string Utility_FileSystem_GetAbsolutePath (const std :: string & P);

// Gets the extension of the specified file (including dot), the letters are NOT changed (no toLower)
// in case the file has no extension, return nullptr
std::string Utility_FileSystem_GetExtension(const std::string& File);

// Gets the upper folder path of the specified path
std::string Utility_FileSystem_GetUpperFolder(const std::string& Path);