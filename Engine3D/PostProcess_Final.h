#pragma once

#include "Shader.h"

//Shader utilizzato per il rendering del frame finale delal camera
//sullo shcermo
class PostProcess_Final : public Shader
{
	GLuint idTextureSampler;

	public:
		PostProcess_Final();
		~PostProcess_Final();

	public:

		//Disenga a schermo il frame della camera finale
		//@param[in] UnitBuffVertex - Buffer dei 6 vertici dello schermo (due triangoli)
		//	NOTA: siccome non vengono effettuate operazioni sui vertici l'altezza e la lunghezza
		//			dello schermo sarà sempre di 1
		//@param[in] TexID - Texture rappresentante il frame della camera
		void DrawFrame(GLuint UnitBuffVertex, GLuint TexID);

	protected:

		void LoadIDVar() override;
};

