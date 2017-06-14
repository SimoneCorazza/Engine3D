#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>

//Classe astratta che rappresenta un generico shader
class Shader
{
	//ATTRIBUTI:
	private:

		GLuint idShader; //ID dello shader secondo OpenGL

	//COSTRUTTORI:
	public:
		Shader();

		~Shader();

	//METODI:
	public:

		//Consente di caricare lo shader
		//@param[in] PathVertexShader - Path al file contenente il codice GLSL del vertex shader
		//@param[in] PathFragmentShader - Path al file contenente il codice GLSL del fragment shader
		//@return True operazione caricamento eseguito con successo False atrimenti
		bool LoadShader(const char* PathVertexShader, const char* PathFragmentShader);

		//GET e SET

		//Ottiene l'id dello shader (0 se non caricato correttamente)
		GLuint getIDShader() const;



	protected:

		//Consente di ottenere l'ID della variabile unifrme indicata nello shader
		//@param[in] Name - Nome della variabile nello shader
		//@return ID della variabile per lo shader
		GLuint GetVarID(const char* Name);

		//Consente di ottenere l'ID della variabile unifrme indicata nello shader
		//@param[in] Name - Nome della variabile nello shader
		//@return ID della variabile per lo shader
		GLuint GetVarID(const std::string& Name);

		//Metodo virtuale da implementare per ottenere i vari ID necessari per le variabili all'interno dello shader
		virtual void LoadIDVar() abstract;



};

