#include "CustomActorScene.hpp"

#include "StandardShader.hpp"
#include "Texture2D.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

#include "MyActor.hpp"

#include <GLFW\glfw3.h>

CustomActorScene::CustomActorScene()
{
}


CustomActorScene::~CustomActorScene()
{
}

void CustomActorScene::InizializeScene()
{
	camera = InsertNewCamera(MeasureMode::MeasureMode_Rate, .0f, .0f, MeasureMode::MeasureMode_Rate, 1.f, 1.f);
	camera->Focus();
	camera->setFaceCulling(FaceCulling::FaceCulling_Back);
	camera->setFrustumCulling(true);
	camera->setProjectionMatrix(45.f, 4.f / 3.f, .6f, 500.f);

	StandardShader* standardShader = new StandardShader();
	standardShader->LoadShader("Standard.vert.glsl", "Texture.frag.glsl");

	// CUBE MODEL CREATION
	Texture2D* textureCube = Texture2D::NewTexture2D("bricks_wall.jpg", GL_RGB,
		GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Material* materialCube = new Material(standardShader, textureCube);
	Mesh* meshCube = Mesh::LoadMSH("cube.msh");
	Model* cube = new Model(meshCube, materialCube);

	// INSERT ACTOR
	Actor* actor1 = new MyActor();
	actor1->setModel(cube);
	InsertNewActor(actor1);
}

void CustomActorScene::UpdateScene(const UpdateParameters & SceneUpdateParameters)
{
	if (getLastInputState()->IsKeyPressed(GLFW_KEY_ESCAPE))
		Terminate();
	else if (getLastInputState()->IsKeyDown(GLFW_KEY_F1))
		camera->SwitchFocus();
}
