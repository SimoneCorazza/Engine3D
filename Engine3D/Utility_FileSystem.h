#pragma once

#include <string>

/*
Insieme di metodi utili per poter lavorare con il file system
*/

//@return Cartella da cui è stato lanciato il processo
std::string& Utility_FileSystem_GetExeFolder();

//Ottiene il percorso assoluto della working directoru corrente
//NECESSITA settare la working directory prima
//std::string Utility_FileSystem_GetAbsolutePath(const std::string& P);

//Ottiene l'estensione del file specificato (punto compreso), le lettere NON vengono modificate (no toLower)
//nel caso il file non abbia estensione ritorna nullptr
std::string Utility_FileSystem_GetExtension(const std::string& File);

//Ottiene la path cartella superiore della path specificata
std::string Utility_FileSystem_GetUpperFolder(const std::string& Path);