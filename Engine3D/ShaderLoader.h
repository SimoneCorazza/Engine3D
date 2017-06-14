#pragma once

#include <GL\glew.h>

#include <string>
#include <fstream>
#include <streambuf>

//Classe che permette di caricare uno shader
class ShaderLoader
{
	private:
		ShaderLoader();
		~ShaderLoader();

	public:

		//Carica uno shader in OpenGL
		//@param[in] VertexPath - Path al file contenente il codice del Vertex shader
		//@param[in] FragmentPath - Path al file contenente il codice del Fragment shader
		//@return 0 in caso di errore, altrimenti l'id dello shader secondo OpenGL
		static GLuint LoadShader(const char* VertexPath, const char* FragmentPath);

		//Carica lo shader indicato in OpenGL
		//@param[in] ShaderType - Tipologia di sahder: GL_FRAGMENT_SHADER, GL_VERTEX_SHADER, ...
		//@param[in] Path - Percorso al file di testo contenente il codice dello shader
		//@return l'id dello shader 0 se lo shader non è stato caricato correttamente
		static GLuint LoadShader(GLint ShaderType, const char* Path);


	private: 

		//Usato per caricare il file di testo con il codice dello sahder
		//@param[in] Path - Path del file di tersto
		//@return Testo contenuto all'interno del file
		static std::string* LoadTextFile(const char* Path);
};

