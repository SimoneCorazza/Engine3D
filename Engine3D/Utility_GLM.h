#pragma once
/*
File contenente metodi di utility, per espandere GLM
*/

#include <glm\glm.hpp>


//Ritorna la matrice che racchiude le informazioni dei seguenti vettori
//Esempio: per rappresentare un modello nello spazio 3D
//@param[in] Location - Vettore della posizione
//@param[in] Scale - Vettore della scala 
//@param[in] Rotation - Vettore della rotazione (indicativa ai singoli assi)
const glm::mat4& Utility_GLM_MatrixFromVectors(const glm::vec3& Location, 
	const glm::vec3& Scale, const glm::vec3& Rotation);