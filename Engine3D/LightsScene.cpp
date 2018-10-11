#include "LightsScene.hpp"

#include "LightTextureShader.hpp"
#include "Texture2D.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

#include <GLFW\glfw3.h>

LightsScene::LightsScene()
{
}


LightsScene::~LightsScene()
{
}

void LightsScene::InizializeScene()
{
	camera = InsertNewCamera(MeasureMode::MeasureMode_Rate, .0f, .0f, MeasureMode::MeasureMode_Rate, 1.f, 1.f);
	camera->Focus();
	camera->setFaceCulling(FaceCulling::FaceCulling_Back);
	camera->setFrustumCulling(true);
	camera->setProjectionMatrix(45.f, 4.f / 3.f, .6f, 500.f);

	LightTextureShader* lightTexture = new LightTextureShader();
	lightTexture->LoadShader("LightTexture.vert.glsl", "LightTexture.frag.glsl");

	// CUBE MODEL CREATION
	Texture2D* textureCube = Texture2D::NewTexture2D("bricks_wall.jpg", GL_RGB,
		GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Material* materialCube = new Material(lightTexture, textureCube);
	Mesh* meshCube = Mesh::LoadMSH("cube.msh");
	Model* cube = new Model(meshCube, materialCube);

	// SPHERE MODEL CREATION
	Texture2D* textureSphere = Texture2D::NewTexture2D("world.jpg", GL_RGB,
		GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Material* materialSphere = new Material(lightTexture, textureSphere);
	Mesh* meshSphere = Mesh::Sphere(glm::vec3(), 1.f, 20, true, true);
	Model* sphere = new Model(meshSphere, materialSphere);

	// SET AMBIENT LIGHT DEFAULT VALUE
	ambientLight = glm::vec3(.5f, .5f, .5f);

	// INSERT ACTORS
	actor1 = new Actor();
	actor1->setModel(cube);
	InsertNewActor(actor1);

	actor2 = new Actor();
	actor2->setModel(sphere);
	actor2->setLocation(0, 0, 10);
	InsertNewActor(actor2);


	// INSERT LIGT
	Light* light0 = InsertNewLight();
	light0->position = glm::vec4(0.0, 5.0, 5.0, 1.0);
	light0->diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
	light0->specular = glm::vec4(1.0, 1.0, 1.0, 1.0);
	light0->constantAttenuation = 0;
	light0->linearAttenuation = 0.1f;
	light0->quadraticAttenuation = 0;
	light0->spotCutoff = 360;
	light0->spotExponent = 0;
	light0->spotDirection = glm::vec3(0, 0, 0);
}

void LightsScene::UpdateScene(const UpdateParameters & SceneUpdateParameters)
{
	if (getLastInputState()->IsKeyPressed(GLFW_KEY_ESCAPE))
		Terminate();
	else if (getLastInputState()->IsKeyDown(GLFW_KEY_F1))
		camera->SwitchFocus();

	actor1->setRotation(actor1->getRotation() + glm::vec3(0, 1, 0) * 50.f * SceneUpdateParameters.getElapsedTime());
	actor2->setRotation(actor1->getRotation() + glm::vec3(0, 1, 0) * 50.f * SceneUpdateParameters.getElapsedTime());
}
