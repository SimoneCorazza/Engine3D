#pragma once

#include "ModelShader.h"

// Shader that allows you to render a model with its texture
// and to apply the lights of the scene
class LightTextureShader : public ModelShader
{
	// Maximum number of lights supported by the shader
	#define MAXIMUM_LIGTS 10

	struct LightUniformIDs
	{
		GLuint idPosition;
		GLuint idDiffuse;
		GLuint idSpecular;
		GLuint idConstantAttenuation, idLinearAttenuation, idQuadraticAttenuation;
		GLuint idSpotCutoff, idSpotExponent;
		GLuint idSpotDirection;
	};

	struct MaterialUniformIDs
	{
		GLuint idAmbient;
		GLuint idDiffuse;
		GLuint idSpecular;
		GLuint idShininess;
	};

	GLuint idM; // ID of the uniform matrix for the model
	GLuint idV; // ID of the uniform matrix for the camera (View)
	GLuint idP; // ID of the uniform matrix for the projection
	GLuint idMTrans; // Id of the uniform matrix M transposed
	GLuint idVInv; // Id of the inverse camera matrix (View)

	GLuint idTextureSampler;

	GLuint idAmbientLight; // Uniform variable for ambient light
	LightUniformIDs lightsArrayComponetsID[MAXIMUM_LIGTS]; // Array containing the IDs of the individual shader struct components
	MaterialUniformIDs materialUniformComponetID; // ID of the uniform shader components for the material
	
	GLuint idLightsNumber; // ID of the variable in the shader indicating the number of lights currently in the array

	public:
		LightTextureShader();
		~LightTextureShader();


	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;
};

