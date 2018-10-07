#include "ShaderLoader.hpp"

#include <vector>


ShaderLoader::ShaderLoader()
{
}


ShaderLoader::~ShaderLoader()
{
}

GLuint ShaderLoader::LoadShader(const char * VertexPath, const char * FragmentPath)
{
	GLuint idVerShader = LoadShader(GL_VERTEX_SHADER, VertexPath);
	GLuint idFragShader = LoadShader(GL_FRAGMENT_SHADER, FragmentPath);

	// Linking the program
	GLuint idProgram = glCreateProgram();
	glAttachShader(idProgram, idVerShader);
	glAttachShader(idProgram, idFragShader);
	glLinkProgram(idProgram);

	GLint result;
	int length;
	// Checking for errors
	glGetProgramiv(idProgram, GL_LINK_STATUS, &result);
	glGetProgramiv(idProgram, GL_INFO_LOG_LENGTH, &length);
	if (result == GL_FALSE)
	{
		std::vector<char> ProgramErrorMessage(length + 1);
		glGetProgramInfoLog(idProgram, length, NULL, &ProgramErrorMessage[0]);
		const char* err = &ProgramErrorMessage[0];
		printf("[GLSL] At %s and %s\n", VertexPath, FragmentPath);
		printf("[GLSL] Link error:%s\n", &ProgramErrorMessage[0]); // I show the error message
	}

	glDeleteShader(idVerShader);
	glDeleteShader(idFragShader);

	return idProgram;

}

GLuint ShaderLoader::LoadShader(GLint ShaderType, const char* Path)
{
	GLuint idShader = glCreateShader(ShaderType);

	// Septum and fill the shader
	std::string* codeChar = LoadTextFile(Path);
	char const* c = codeChar->c_str();
	glShaderSource(idShader, 1, &c, NULL);
	glCompileShader(idShader);

	delete codeChar; // I delete the characters
	
	// Check for errors
	GLint result = GL_FALSE;
	int infoLogLength;
	glGetShaderiv(idShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (result == GL_FALSE) // There are errors
	{
		std::vector<char> shaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(idShader, infoLogLength, NULL, &shaderErrorMessage[0]);
		const char* err = &shaderErrorMessage[0];
		printf("[GLSL] At %s\n", Path);
		printf("[GLSL] Compile error:%s\n", &shaderErrorMessage[0]); // I show the error message
	}

	return idShader;

}

std::string* ShaderLoader::LoadTextFile(const char * Path)
{
	std::ifstream t(Path);
	std::string* str = new std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>()); // I read all the input file
	t.close();

	return str;
}
