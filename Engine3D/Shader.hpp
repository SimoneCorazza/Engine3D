#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>

// Abstract class representing a generic shader
class Shader
{
	// ATTRIBUTES:
	private:

		// Shader ID according to OpenGL
		GLuint idShader;

	// CONSTRUCTORS:
	public:
		Shader();

		~Shader();

	// METHODS:
	public:

		// Allows you to load the shader
		// @param[in] PathVertexShader - Path to the file containing the GLSL code of the vertex shader
		// @param[in] PathFragmentShader - Path to the file containing the GLSL code of the fragment shader
		// @return True operation loading successfully performed False otherwise
		bool LoadShader(const char* PathVertexShader, const char* PathFragmentShader);

		// GET and SET

		// Gets the shader id (0 if not loaded correctly)
		GLuint getIDShader() const;



	protected:

		// Obtains the ID of the uniform variable indicated in the shader
		// @param in] Name - Name of the variable in the shader
		// @return ID of the variable for the shader
		GLuint GetVarID(const char* Name);

		// Obtains the ID of the uniform variable indicated in the shader
		// @param[in] Name - Name of the variable in the shader
		// @return ID of the variable for the shader
		GLuint GetVarID(const std::string& Name);

		// Virtual method to implement to get the various IDs needed for the variables within the shader
		virtual void LoadIDVar() abstract;



};

