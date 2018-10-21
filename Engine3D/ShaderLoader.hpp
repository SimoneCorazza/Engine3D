#pragma once

#include <GL\glew.h>

#include <string>
#include <fstream>
#include <streambuf>

// Class that allows you to load a shader
class ShaderLoader
{
	private:
		ShaderLoader();
		~ShaderLoader();

	public:

		// Upload a shader in OpenGL
		// @param[in] VertexPath - Path to the file containing the Vertex shader code
		// @param[in] FragmentPath - Path to the file containing the Fragment shader code
		// @return 0 in case of error, otherwise the shader id according to OpenGL
		static GLuint LoadShader(const char* VertexPath, const char* FragmentPath);

		// Load the shader indicated in OpenGL
		// @param[in] ShaderType - Type of sahder: GL_FRAGMENT_SHADER, GL_VERTEX_SHADER, ...
		// @param[in] Path - Path to the text file containing the shader code
		// @return the shader id 0 if the shader has not been loaded correctly
		static GLuint LoadShader(GLint ShaderType, const char* Path);


	private: 

		// Used to load the text file with the sahder code
		// @param[in] Path - Path to the text file
		// @return Text contained within the file
		static std::string* LoadTextFile(const char* Path);
};

