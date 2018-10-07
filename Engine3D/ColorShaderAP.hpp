#pragma once

#include <glm\glm.hpp>
#include "ActorParameters.hpp"

class ColorShaderAP : public ActorParameters
{
	public:
		// Color of the model
		glm::vec4 color = glm::vec4(0, 0, 0, 0);

	public:
		ColorShaderAP();
		~ColorShaderAP();
};

