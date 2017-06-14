#include "Utility_FileSystem.h"
#include "Utility_Math.h"

#ifdef WINDOWS
#include <Windows.h>
#endif

std::string workingDirectory; //Attuale cartella contenente l'eseguibile

void Utility_FileSystem_InizializeWorkingDirectory()
{
	//Ottengo la path usando la API sel sistema operativo in uso
#ifdef WINDOWS
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileName(hModule, path, MAX_PATH);

	char ch[MAX_PATH];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, path, -1, ch, 260, &DefChar, NULL); //Converto in char 

	workingDirectory = Utility_FileSystem_GetUpperFolder(std::string(ch));
#else
#error Unknown plattform: cannot get the path of the exe
#endif
}

/*
std::string Utility_FileSystem_GetAbsolutePath(const std::string& P)
{
	//Ritorno: "workingDirectory + \\ + P", il separatore è stato messo per ragioni di sicurezza (potrebbe non esserci)
	return workingDirectory + "\\" + P;
}
*/



std::string& Utility_FileSystem_GetExeFolder()
{
	if (workingDirectory.size() == 0) //Nel caso non sia stata ancora settata la cartella
		Utility_FileSystem_InizializeWorkingDirectory();

	return workingDirectory;
}

std::string Utility_FileSystem_GetExtension(const std::string& File)
{
	std::string f(File);
	size_t pos = f.find_last_of('.');

	if (pos == std::string::npos)
		return std::string(); //Caso estensione non trovata
	else
		return f.substr(pos, f.size() - pos);
}


std::string Utility_FileSystem_GetUpperFolder(const std::string& Path)
{
	std::string p(Path);
	size_t posBackSlash = p.find_last_of('\\');
	size_t posSlash = p.find_last_of('/');
	//Vado a considerare la posizione maggiore tra le due (nota: se è MAX_UNSIGNED_INT o std::string::npos vuol dire che non è stato trovato)
	size_t pos;
	if (posBackSlash == std::string::npos) //Caso il \ non ci sia
		pos = posSlash;
	else if (posSlash == std::string::npos) //Caso il / non ci sia
		pos = posBackSlash;
	else
		pos = MAX(posBackSlash, posSlash); //Se sono presenti entrambi prendo il massimo tra i due

	if (pos <= 1 || pos == std::string::npos) //Stringa del tipo: "\", "a\", "C\", "a", "abc123" ...
		return nullptr; //Ritorno errore
	else if (p.size() == 3) //caso abbia la dimensione minima (root) "C:\", "D:\", ...
	{
		//Ritorno la stessa stringa
		return Path;
	}
	else if(pos == p.size() - 1) //Caso sia posizionato come ultimo carattere
		return Utility_FileSystem_GetUpperFolder(p.substr(0, p.size() - 1).c_str()); //Ottengo la path della cartella escludendo l'ultimo separatore
	else
	{
		return p.substr(0, pos + 1); //Elimino l'ultima parte della path
	}
}