#include "ShadersWithParametersScene.hpp"

#include "Texture2D.hpp"
#include "Model.hpp"
#include "Mesh.hpp"
#include "StandardShader.hpp"
#include "Material.hpp"
#include "Actor.hpp"

#include "LiftTriShader.hpp"
#include "ColorShader.hpp"

#include "MyColorActor.hpp"
#include "MyLiftTriActor.hpp"

#include <GLFW\glfw3.h>

ShadersWithParametersScene::ShadersWithParametersScene()
{
}


ShadersWithParametersScene::~ShadersWithParametersScene()
{
}

void ShadersWithParametersScene::InizializeScene()
{
	camera = InsertNewCamera(MeasureMode::MeasureMode_Rate, .0f, .0f, MeasureMode::MeasureMode_Rate, 1.f, 1.f);
	camera->Focus();
	camera->setFaceCulling(FaceCulling::FaceCulling_Back);
	camera->setFrustumCulling(true);
	camera->setProjectionMatrix(45.f, 4.f / 3.f, .6f, 500.f);

	LiftTriShader* liftTriShader = new LiftTriShader();
	liftTriShader->LoadShader("LiftTri.vert.glsl", "Texture.frag.glsl");

	ColorShader* colorShader = new ColorShader();
	colorShader->LoadShader("Standard.vert.glsl", "Color.frag.glsl");

	// CUBE MODEL CREATION
	Texture2D* textureCube = Texture2D::NewTexture2D("bricks_wall.jpg", GL_RGB,
		GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Material* materialCube = new Material(liftTriShader, textureCube);
	Mesh* meshCube = Mesh::LoadMSH("cube.msh");
	Model* cube = new Model(meshCube, materialCube);

	// SPHERE MODEL CREATION
	Texture2D* textureSphere = Texture2D::NewTexture2D("world.jpg", GL_RGB,
		GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Material* materialSphere = new Material(colorShader, textureSphere);
	Mesh* meshSphere = Mesh::Sphere(glm::vec3(), 1.f, 20, true, true);
	Model* sphere = new Model(meshSphere, materialSphere);

	// INSERT ACTORS
	Actor* actor1 = new MyLiftTriActor();
	actor1->setModel(cube);
	InsertNewActor(actor1);

	Actor* actor2 = new MyColorActor();
	actor2->setModel(sphere);
	actor2->setLocation(5, 0, 0);
	InsertNewActor(actor2);
}

void ShadersWithParametersScene::UpdateScene(const UpdateParameters & SceneUpdateParameters)
{
	if (getLastInputState()->IsKeyPressed(GLFW_KEY_ESCAPE))
		Terminate();
	else if (getLastInputState()->IsKeyDown(GLFW_KEY_F1))
		camera->SwitchFocus();
}
