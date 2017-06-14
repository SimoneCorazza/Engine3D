#pragma once

#include <GL\glew.h>

#include "Shader.h"

class PostProcessShaderParams;

//Classe atratta che rappresenta uno shader dedicato alla modifica du un immagine a rendering avvenuto
class PostProcessShader : public Shader
{
	GLuint idRenderedTexture; //ID della texture contenente il frame renderizzato
	GLuint idDepthTexture; //ID della texture contenente la profondità nel frame

	public:
		PostProcessShader();
		~PostProcessShader();


	public:

		//Consente di applicare lo shader
		//@param[in] IdBufferUnitQuad - Id del buffer contenente un quadrato di lato 2 con il centro nell'origine
		//	ed è composto da due triangoli (6 vertici nel buffer)
		//@param[in] RenderedTextureID - Texture ID secondo OpenGL del frame renderizzato
		//@param[in] DepthTextureID - Texture ID secondo OpenGL del depth buffer della scena renderizzata
		//@param[in] Params - Parametri per lo shader
		void ApplayShader(GLuint IdBufferUnitQuad, GLuint RenderedTextureID, GLuint DepthTextureID, const PostProcessShaderParams* Params) const;

	protected:

		//Metodo da derivare che consente di impostare i parametri
		//@param[in] Params - Parametri per lo shader
		virtual void SetShaderParams(const PostProcessShaderParams* Params) const abstract;

		void LoadIDVar() override;
};

