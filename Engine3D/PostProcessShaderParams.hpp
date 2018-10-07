#pragma once

#include <glm\glm.hpp>

class Camera;

// Class representing a series of parameters to be passed to the PostProcessShader
class PostProcessShaderParams
{
	glm::vec2 resolution;

	public:
		PostProcessShaderParams();

		~PostProcessShaderParams();

	public:

		// Sets the resolution of the portion of the video where the shader is applied
		void setResolution(const glm::vec2& R);
		// Gets the resolution of the portion of the video where the shader is applied
		glm::vec2 getResolution() const;

		// Gets the time passed since the application started at this precise moment
		static float getCurrentTime();
};

