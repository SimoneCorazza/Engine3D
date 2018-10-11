#include "PostProcessScene.hpp"

#include "StandardShader.hpp"
#include "Texture2D.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "PostProcessShaderParams.hpp"

#include <GLFW\glfw3.h>

PostProcessScene::PostProcessScene()
{
}


PostProcessScene::~PostProcessScene()
{
}

void PostProcessScene::InizializeScene()
{
	camera = InsertNewCamera(MeasureMode::MeasureMode_Rate, .0f, .0f, MeasureMode::MeasureMode_Rate, 1.f, 1.f);
	camera->Focus();
	camera->setFaceCulling(FaceCulling::FaceCulling_Back);
	camera->setFrustumCulling(true);
	camera->setProjectionMatrix(45.f, 4.f / 3.f, .6f, 500.f);

	StandardShader* standardShader = new StandardShader();
	standardShader->LoadShader("Standard.vert.glsl", "Texture.frag.glsl");


	// POST PROCESS CREATIONS
	blackAndWhite = new BlackAndWhitePostProcessShader();
	blackAndWhite->LoadShader("PostProcess_Common.vert.glsl", "PostProcess_BlackWhite.frag.glsl");

	postBlur = new BlurPostProcessShader();
	postBlur->LoadShader("PostProcess_Common.vert.glsl", "PostProcess_Blur.frag.glsl");

	postDepth = new DepthPostProcessShader();
	postDepth->LoadShader("PostProcess_Common.vert.glsl", "PostProcess_Depth.frag.glsl");
	

	// CUBE MODEL CREATION
	Texture2D* textureCube = Texture2D::NewTexture2D("bricks_wall.jpg", GL_RGB,
		GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Material* materialCube = new Material(standardShader, textureCube);
	Mesh* meshCube = Mesh::LoadMSH("cube.msh");
	Model* cube = new Model(meshCube, materialCube);

	// SPHERE MODEL CREATION
	Texture2D* textureSphere = Texture2D::NewTexture2D("world.jpg", GL_RGB,
		GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Material* materialSphere = new Material(standardShader, textureSphere);
	Mesh* meshSphere = Mesh::Sphere(glm::vec3(), 1.f, 20, true, true);
	Model* sphere = new Model(meshSphere, materialSphere);

	// INSERT ACTORS
	Actor* actor1 = new Actor();
	actor1->setModel(cube);
	InsertNewActor(actor1);

	Actor* actor2 = new Actor();
	actor2->setModel(sphere);
	actor2->setLocation(5, 0, 0);
	InsertNewActor(actor2);
}

void PostProcessScene::UpdateScene(const UpdateParameters & SceneUpdateParameters)
{
	if (getLastInputState()->IsKeyPressed(GLFW_KEY_ESCAPE))
		Terminate();
	else if (getLastInputState()->IsKeyDown(GLFW_KEY_F1))
		camera->SwitchFocus();

	if (SceneUpdateParameters.getInputState()->IsKeyDown(GLFW_KEY_1))
	{
		RemoveCurrentEffect();
		currentEffect = camera->AddPostProcessEffect(blackAndWhite, nullptr);
	}
	else if (SceneUpdateParameters.getInputState()->IsKeyDown(GLFW_KEY_2))
	{
		RemoveCurrentEffect();
		currentEffect = camera->AddPostProcessEffect(postBlur, new PostProcessShaderParams());
	}
	else if (SceneUpdateParameters.getInputState()->IsKeyDown(GLFW_KEY_3))
	{
		RemoveCurrentEffect();
		currentEffect = camera->AddPostProcessEffect(postDepth, nullptr);
	}
	else if (SceneUpdateParameters.getInputState()->IsKeyDown(GLFW_KEY_0))
	{
		RemoveCurrentEffect();
	}
}

void PostProcessScene::RemoveCurrentEffect()
{
	if (currentEffect == nullptr)
	{
		return;
	}
	currentEffect->RemoveFromCamera();
}
