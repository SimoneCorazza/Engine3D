#include "Utility_FileSystem.hpp"
#include "Utility_Math.hpp"

#ifdef WINDOWS
#include <Windows.h>
#endif

std::string workingDirectory; // Current folder containing the executable

void Utility_FileSystem_InizializeWorkingDirectory()
{
	// I get the path using the API of the operating system in use
#ifdef WINDOWS
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileName(hModule, path, MAX_PATH);

	char ch[MAX_PATH];
	char DefChar = ' ';

	// Convert to char
	WideCharToMultiByte(CP_ACP, 0, path, -1, ch, 260, &DefChar, NULL);

	workingDirectory = Utility_FileSystem_GetUpperFolder(std::string(ch));
#else
#error Unknown plattform: cannot get the path of the exe
#endif
}



std::string& Utility_FileSystem_GetExeFolder()
{
	// In case the folder has not been set yet
	if (workingDirectory.size() == 0)
		Utility_FileSystem_InizializeWorkingDirectory();

	return workingDirectory;
}

std::string Utility_FileSystem_GetExtension(const std::string& File)
{
	std::string f(File);
	size_t pos = f.find_last_of('.');

	if (pos == std::string::npos)
		return std::string(); // Extension case not found
	else
		return f.substr(pos, f.size() - pos);
}


std::string Utility_FileSystem_GetUpperFolder(const std::string& Path)
{
	std::string p(Path);
	size_t posBackSlash = p.find_last_of('\\');
	size_t posSlash = p.find_last_of('/');
	// I'm going to consider the greater position between the two (note: if it's MAX_UNSIGNED_INT or std::string::npos means it was not found)
	size_t pos;
	if (posBackSlash == std::string::npos) // Case \ is not there
		pos = posSlash;
	else if (posSlash == std::string::npos) // Case / there is not
		pos = posBackSlash;
	else
		pos = MAX(posBackSlash, posSlash); // If both are present I take the maximum between the two

	if (pos <= 1 || pos == std::string::npos) // String of the type: "\", "a \", "C \", "a", "abc123" ...
		return nullptr; // Return error
	else if (p.size() == 3) // If the minimum size (root) is "C: \", "D: \", ...
	{
		// Return the same string
		return Path;
	}
	else if(pos == p.size() - 1) // Case is positioned as the last character
		return Utility_FileSystem_GetUpperFolder(p.substr(0, p.size() - 1).c_str()); // I get the path of the folder excluding the last separator
	else
	{
		return p.substr(0, pos + 1); // I delete the last part of the path
	}
}