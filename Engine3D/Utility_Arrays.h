#pragma once

/*
Insieme di metodi con lo scopo di fornire dei metodid utili a manipolare degli array
*/



//Copia una porzione di matrice indicata dalla dimensione indicata
//@param[in] OffsetX - Coordinata X del punto d'inizio della sub-matrix in numero di elementi
//@param[in] OffsetY - Coordinata Y del punto d'inizio della sub-matrix in numero di elementi
//@param[in] Width - Dimensione sull'asse X della sub-matrix in numero di elementi
//@param[in] Height - Dimensione sull'asse Y della sub-matrix in numero di elementi 
//@param[in] SizeElement - Dimensione di un'elemento in bytes > 0
//@param[in] Matrix - Matrice da cui ricavare la sub-matrix
//@param[in] MatrixWid - Numero di colonne della matrice (in numero di elementi)
//@param[in] MatrixHei - Numero di righe della matrice (in numero di elementi)
void* Utility_Arrays_SubMatrix(const size_t& OffsetX, const size_t& OffsetY, const size_t& Width, const size_t& Height, const size_t& SizeElement, 
	void* Matrix, const size_t& MatrixWid, const size_t& MatrixHei);