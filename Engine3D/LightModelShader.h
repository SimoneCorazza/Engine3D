#pragma once

#include "ModelShader.h"

// Abstract class that allows to represent a used shader
// to render a model with light effects
class LightModelShader : public ModelShader
{
	public:
		LightModelShader();
		~LightModelShader();

	public:

		// Set the ambient light to apply to the model
		// (minimum light that owns the object)
		virtual void setAmbientLight(glm::vec3 AbientLight) const abstract;


};

