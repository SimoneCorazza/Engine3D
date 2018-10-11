#include "StressTestScene.hpp"

#include <GLFW\glfw3.h>
#include "Texture2D.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "TextureCube.hpp"
#include "StandardShader.hpp"


StressTestScene::StressTestScene()
{
}


StressTestScene::~StressTestScene()
{
}


void StressTestScene::InizializeScene()
{
	camera = InsertNewCamera(MeasureMode::MeasureMode_Rate, .0f, .0f, MeasureMode::MeasureMode_Rate, 1.f, 1.f);
	camera->Focus();
	camera->setFaceCulling(FaceCulling::FaceCulling_Back);
	camera->setFrustumCulling(true);
	camera->setProjectionMatrix(45.f, 4.f / 3.f, .6f, 500.f);


	StandardShader* standardShader = new StandardShader();
	standardShader->LoadShader("Standard.vert.glsl", "Texture.frag.glsl");

	// SKYBOX
	TextureCube* texCube = TextureCube::NewTextureCube("Cubemap3.png", GL_RGB,
		GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, 
		GL_CLAMP_TO_EDGE, true);
	Skybox* box = new Skybox(Mesh::CubeInternal(glm::vec3(0, 0, 0), 1), texCube);
	InsertSkybox(box);

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

	// Put actors in the scene
	for (int x = 0; x < NUM_ACT_X; x++)
		for (int y = 0; y < NUM_ACT_Y; y++)
			for (int z = 0; z < NUM_ACT_Z; z++)
			{
				actor[x][y][z] = new Actor();
				if ((z + x + y) % 2 == 0)
				{
					actor[x][y][z]->setModel(sphere);
				}
				else
				{
					actor[x][y][z]->setModel(cube);
				}
				actor[x][y][z]->setLocation(x * 2.5f, y * 3.f, z * 2.5f);
				InsertNewActor(actor[x][y][z]);
			}


	Font* fnt = new Font();
	fnt->Load("arial.ttf", 60);
	txt = new TextBox();
	txt->setArea(Rectangle(0, 0, 10, 20));
	txt->setFont(fnt);
	txt->setTextColor(glm::vec4(1, 0, 0, 1));
	getUI().Add(txt);
}

void StressTestScene::UpdateScene(const UpdateParameters & SceneUpdateParameters)
{
	if (getLastInputState()->IsKeyPressed(GLFW_KEY_ESCAPE))
		Terminate();
	else if (getLastInputState()->IsKeyDown(GLFW_KEY_F1))
		camera->SwitchFocus();

	std::string act = std::to_string(getRenderingEngineInfo().renderedActors);
	txt->setText(act + "\t " + std::to_string(1.0f / SceneUpdateParameters.getElapsedTime()));
}
