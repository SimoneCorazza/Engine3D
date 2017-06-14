#include "PostProcessEffect.h"

#include "Camera.h"
#include "DEBUG.h"

PostProcessEffect::PostProcessEffect(unsigned int ID, Camera* Camera, const PostProcessShader* PostProcessShader, PostProcessShaderParams* PostProcessShaderParams)
{
	id = ID;
	camera = Camera;
	postProcessShader = PostProcessShader;
	postProcessShaderParams = PostProcessShaderParams;
}


PostProcessEffect::~PostProcessEffect()
{
}




void PostProcessEffect::RemoveFromCamera()
{
	if (camera == nullptr)
		ASSERT(false, "Camera not set");
	else
		camera->RemovePostProcessEffect(id);
}

unsigned int PostProcessEffect::getID() const
{
	return id;
}

const PostProcessShader * PostProcessEffect::getPostProcessShader() const
{
	return postProcessShader;
}

PostProcessShaderParams* PostProcessEffect::getPostProcessShaderParams()
{
	return postProcessShaderParams;
}
