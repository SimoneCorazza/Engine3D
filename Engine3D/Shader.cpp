#include "Shader.hpp"
#include "ShaderLoader.hpp"


Shader::Shader()
{
	idShader = 0;
}


Shader::~Shader()
{

}



bool Shader::LoadShader(const char* PathVertexShader, const char* PathFragmentShader)
{
	// Return true if everything is OK false otherwise (== 0 -> error)
	idShader = ShaderLoader::LoadShader(PathVertexShader, PathFragmentShader);
	bool r = idShader != 0;
	if (r)
		LoadIDVar(); // Load the various IDs of the shader variables (abstract method)
	else
		idShader = 0; // In case of error

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

GLuint Shader::getIDShader() const
{
	return idShader;
}
