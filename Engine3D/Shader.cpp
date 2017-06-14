#include "Shader.h"
#include "ShaderLoader.h"

//--- COSTRUTTORI ---

Shader::Shader()
{
	idShader = 0;
}


Shader::~Shader()
{

}


//--- METODI ---

bool Shader::LoadShader(const char* PathVertexShader, const char* PathFragmentShader)
{
	//Ritorno true se è tutto OK false altrimenti (== 0 -> errore)
	idShader = ShaderLoader::LoadShader(PathVertexShader, PathFragmentShader);
	bool r = idShader != 0;
	if (r)
		LoadIDVar(); //Carico i vari ID delle variabili dello shader (metodo astratto)
	else
		idShader = 0; //In caso di errore

	return r;
}

GLuint Shader::GetVarID(const char* Nome)
{
	return glGetUniformLocation(idShader, Nome);
}

GLuint Shader::GetVarID(const std::string & Name)
{
	return GetVarID(Name.c_str());
}

//GET e SET

GLuint Shader::getIDShader() const
{
	return idShader;
}
