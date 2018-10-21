#pragma once

class PostProcessShader;
class PostProcessShaderParams;

class Camera;

// Class that wraps the information for the applicazion of a post process shader
class PostProcessEffect
{
	unsigned int id;
	Camera* camera;

	const PostProcessShader* postProcessShader;
	PostProcessShaderParams* postProcessShaderParams;

	public:
		PostProcessEffect(unsigned int ID, Camera* Camera, const PostProcessShader* PostProcessShader, PostProcessShaderParams* PostProcessShaderParams);

		~PostProcessEffect();

	public:

		// Removes this effect from the camera
		void RemoveFromCamera();


		// Gets the id of this effect instance in the camera
		unsigned int getID() const;

		// Gets the shader to use for this effect
		const PostProcessShader* getPostProcessShader() const;

		// Gets the parameters for the shader
		PostProcessShaderParams* getPostProcessShaderParams();
};

