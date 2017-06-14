#include "RenderingEngine.h"


#include "DEBUG.h"

#include <vector>
#include "Actor.h"
#include "Scene.h"
#include "Material.h"
#include "Mesh.h"
#include "Frustum.h"
#include "InputEngine.h"
#include "Skybox.h"
#include "PostProcessShader.h"
#include "PostProcessShaderParams.h"
#include "Rectangle.h"
#include "ModelShader.h"

#include "Font.h"
#include "SpriteFont.h"
#include <glm\gtc\matrix_transform.hpp>

#include "CommonConstants.h"

#ifdef _DEBUG
/*
	#include "ColorShader.h"
	ColorShader shaderColorDebug; //Shader usato per debuggare
	GLuint idBuff_BoxFrustum; //Id del buffer del frustum (per visualizzare il frustum box a video)
	#define SIZE_BUFF_LINES_BOX (72 * 4) //Dimensione in byte dell'array contenente le coordinate delle linee per il box
*/
#endif
	
GLuint RenderingEngine::idBuffUnitQuad = 0;

//Buffer contenente un quadrato di lato 2, posizionato sull'origine
//il quadrato è formato da due triangoli separati
GLfloat bufferUnitVerteces[] =
{
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f,  1.0f, 0.0f,
};


RenderingEngine::RenderingEngine()
{
}


RenderingEngine::~RenderingEngine()
{

}


void RenderingEngine::Inizialize()
{
	//Imposto il colore di background
	setBackgroundColor(glm::vec4(0, 0, 1, 0));

	//Abilito il test della profondità:
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //Test di profondità da eseguire: accetto il nuovo pixel (ottenuto dal fragment-shader) se è più vicino di quello che è già memorizzato

	if (idBuffUnitQuad == 0) //Controllo se il buffer è stato inizializzato in precedenza
	{
		//Genero il buffer
		glGenBuffers(1, &idBuffUnitQuad);
		glBindBuffer(GL_ARRAY_BUFFER, idBuffUnitQuad);
		glBufferData(GL_ARRAY_BUFFER, sizeof(bufferUnitVerteces), bufferUnitVerteces, GL_STREAM_DRAW);
	}

	//Carico lo shader per il passaggio da framebuffer a schermo
	postProcess_final.LoadShader("PostProcess_Common.vert.glsl", "Texture.frag.glsl");
	//Carico lo shader per il rendering dello skybox
	skyboxShader.LoadShader("Skybox.vert.glsl", "Skybox.frag.glsl");


	//Per il disegno dell'interfaccia
	draw2d.Inizialize();

#ifdef _DEBUG
/*
	shaderColorDebug.LoadShader("VertecesOnly.vert.glsl", "Color.frag.glsl");

	//Genero il buffer di debug per il box del frutum
	glGenBuffers(1, &idBuff_BoxFrustum);
	glBindBuffer(GL_ARRAY_BUFFER, idBuff_BoxFrustum);
	glBufferData(GL_ARRAY_BUFFER, SIZE_BUFF_LINES_BOX, nullptr, GL_STREAM_DRAW);
*/
#endif
}

void RenderingEngine::WindowResized(int Width, int Height)
{
	draw2d.SetWindowSize(Width, Height);
}

void RenderingEngine::setBackgroundColor(const glm::vec4& C)
{
	backgroundColor = C;
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
}

void RenderingEngine::EnableArraysShader(const ModelShader* S)
{
	GLuint idCord = S->getIDVertecesCoords();
	GLuint idUV = S->getIDVertecesUVs();
	GLuint idNorm = S->getIDVertecesNormals();

	//Controllo se lo shader supporta/richiede le UV e/o le normali
	bool uvs = idUV != INVALID_BUFFER_ID;
	bool normals = idNorm != INVALID_BUFFER_ID;

	glEnableVertexAttribArray(idCord);
	if (uvs) //Disabilito solo se le UV sono supporta/richieste dallo shader
		glEnableVertexAttribArray(idUV);
	if (normals) //Disabilito solo se le normali sono supporta/richieste dallo shader
		glEnableVertexAttribArray(idNorm);
}

void RenderingEngine::SetArraysShader(const ModelShader* S, const Mesh * M)
{
	GLuint idCord = S->getIDVertecesCoords();
	GLuint idUV = S->getIDVertecesUVs();
	GLuint idNorm = S->getIDVertecesNormals();

	//Controllo se lo shader supporta/richiede le UV e/o le normali
	bool uvs = idUV != INVALID_BUFFER_ID;
	bool normals = idNorm != INVALID_BUFFER_ID;

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, M->getIDBuffVerteces());
	glVertexAttribPointer(
		idCord,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	if (uvs) //Controllo se lo sahder supporta/richiede le UV
	{
		// 2nd attribute buffer : UVs
		glBindBuffer(GL_ARRAY_BUFFER, M->getIDBuffUV());
		glVertexAttribPointer(
			idUV,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);
	}

	if (normals) //Controllo se lo sahder supporta/richiede le normali
	{
		// 3nd attribute buffer : Normals
		glBindBuffer(GL_ARRAY_BUFFER, M->getIDBuffNormals());
		glVertexAttribPointer(
			idNorm,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);
	}
}

void RenderingEngine::DisableArrayShader(const ModelShader* S)
{
	GLuint idCord = S->getIDVertecesCoords();
	GLuint idUV = S->getIDVertecesUVs();
	GLuint idNorm = S->getIDVertecesNormals();

	//Controllo se lo shader supporta/richiede le UV e/o le normali
	bool uvs = idUV != INVALID_BUFFER_ID;
	bool normals = idNorm != INVALID_BUFFER_ID;

	glDisableVertexAttribArray(idCord);
	if (uvs) //Disabilito solo se le UV sono supporta/richieste dallo shader
		glDisableVertexAttribArray(idUV);
	if (normals) //Disabilito solo se le normali sono supporta/richieste dallo shader
		glDisableVertexAttribArray(idNorm);
}

void RenderingEngine::RenderScene(Scene& S)
{
	//Ordino gli attori per il rendering:
	//Time_Now();
	S.SortActors();
	//TIME_POP("Sort time: ");

	const Point2 windowSize = S.getLastInputState()->getWindowSize();

	//Ottengo la serie di items della scena da renderizzare
	const std::vector<Actor*>* actors = S.getActors();
	MapIterator<unsigned int, Camera*> cam = S.getCameras();
	MapIterator<unsigned int, Light*> lig = S.getLigths();


	Frustum frustum; //Classe usata per effettuare il frustrum degli attori nella scena

	//--- CAMERE ---
	while(cam.hasNext()) //Ciclo per le camere
	{
		const Camera* camera = cam.next(); //Puntatore alla camera attuale

		ASSERT(camera != nullptr, "Camera cannot be null");

		const Point2 o = camera->getOffset();
		const Point2 s = camera->getSize();
		Rectangle cameraPortion(o.x, windowSize.y - (o.y + s.y), s.x, s.y); //Ottengo la porzione di camera utilizzata dalla camera
		const bool frustumCulling = camera->getFrustumCulling(); //Indica se il frustum culling è abilitato dalla camera

		glBindFramebuffer(GL_FRAMEBUFFER, camera->getFrameBufferID()); //Uso il frame buffer della camera
		camera->changePostProcessRenderTexture(0); //Imposto sempre come prima texture su cui renderizzare la prima (numero 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Pulisco il frame buffer
		glViewport(cameraPortion.x, cameraPortion.y, cameraPortion.width, cameraPortion.height); //Renderizzo la camera nella sua posizione (invertendo l'asse Y)

		
		RenderSkybox(S.getSkyBox(), *camera); //Renderizzo lo skybox se presente, per questa camera

		const bool cameraCullFace = camera->getFaceCulling() != FaceCulling::FaceCulling_Disabled; //Indica se il face culling è attivato dalla camera
		bool cullFace = cameraCullFace; //Stato attuale del culling delle faccie
		//Per il face culling impostato dalla camera:
		if (cullFace)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(camera->getFaceCulling()); //Setto la modalità desiderata dalla camera
		}
		else
			glDisable(GL_CULL_FACE);

		frustum.setPlanes(camera->getCameraMatrix()); //Imposto i piani di clipping per il frustrum

		//--- LUCI ---
		std::vector<Light*> activeLights; //Vettore per le luci per renderizzare
		//Ciclo per eliminare le luci spente o troppo lontane
		while (lig.hasNext())
		{
			Light* l = lig.next();
			if (l->state && frustum.TestView(glm::vec3(l->position), l->getClippingRadius())) //Se accesa e nel frustum, aggiungo la luce nella lista
				activeLights.push_back(l);
		}


		info.renderedActors = 0; //Contatore per il numero di attori renderizzati
		info.renderedTriangles = 0; //Contatore per i triangoli renderizzati
		const Actor* lastActor = nullptr; //Ultimo attore renderizzato
		//---- ATTORI -----
		for (int i = 0; i < actors->size(); i++) //Ciclo per il rendering degli attori
		{
			const Actor* a = (*actors)[i];
			Box* b = a->getModel()->getMesh()->getFrustumBox() * a->getModelMatrix();

			//Controllo che il frustum culling sia abilitato dalla camera, e in tal caso testo se l'attore è nel frustum
			//atrimenti senza frustum, disegno sempre l'attore
			if (!frustumCulling || frustum.TestView(b))
			{
				info.renderedActors++; //Contatore attori renderizzati

				const Model* m = a->getModel();
				const Material* mat = m->getMaterial();
				ModelShader* s = mat->getShader();

				info.renderedTriangles += m->getMesh()->getVertecesDraw() / 3;

				//Caso sia il primo attore da renderizzare oppure se si è cambiato shader per il rendering
				if (lastActor == nullptr || lastActor->getModel()->getMaterial()->getShader()->getIDShader() != s->getIDShader())
				{
					//Chiudo gli attributi per lo sahder usato in precedenza per renderizzare l'ultimo attore (se c'è stato un'attore precedente)
					if(lastActor != nullptr)
						DisableArrayShader(lastActor->getModel()->getMaterial()->getShader());

					//Abilito/disabilito il face culling in base alle esigenze dello shader
					if (s->getBothSide()) //Caso lo shader richieda che vengano renderizzate tutte le faccie
					{
						if (cullFace)
						{
							glDisable(GL_CULL_FACE);
							cullFace = false;
						}
					}
					else
					{
						if (!cullFace)
						{
							glEnable(GL_CULL_FACE);
							cullFace = true;
						}
					}


					//Setto gli attributi globali per il nuovo shader:
					glUseProgram(s->getIDShader());
					s->SetSceneLights(activeLights);
					s->SetAmbientLight(S.getAmbientLight());
					s->SetCameraParameters(camera->getViewMatrix(), camera->getProjectionMatrix());
					s->SetMaterial(a->getModel()->getMaterial());

					EnableArraysShader(s);
					SetArraysShader(s, a->getModel()->getMesh()); //Setto i buffer per la mesh del modello
				}
				else
				{
					if (m->getMaterial() != lastActor->getModel()->getMaterial()) //Caso sia cambiato il materiale (compresa anche la texture)
						s->SetMaterial(a->getModel()->getMaterial()); //Setto gli attributi dello sahder per il nuovo materiale

					if (m->getMesh() != lastActor->getModel()->getMesh()) //Caso si sia cambiata la mesh
						SetArraysShader(s, m->getMesh()); //Setto gli attributi dello sahder per la nuova mesh
				}

				s->SetObjectParameters(a->getActorParameters(), a->getModelMatrix()); //Impostazioni per lo shader per questo oggetto
				glDrawArrays(GL_TRIANGLES, 0, m->getMesh()->getVertecesDraw()); //Rendering della mesh

				/*
				#ifdef _DEBUG
				glDisable(GL_DEPTH_TEST);

				float arr[] =
				{
					//Faccia inferiore:
					b->v1.x, b->v1.y, b->v1.z,
					b->v2.x, b->v2.y, b->v2.z,

					b->v2.x, b->v2.y, b->v2.z,
					b->v3.x, b->v3.y, b->v3.z,

					b->v3.x, b->v3.y, b->v3.z,
					b->v4.x, b->v4.y, b->v4.z,

					b->v4.x, b->v4.y, b->v4.z,
					b->v1.x, b->v1.y, b->v1.z,

					//Faccia superiore:
					b->v5.x, b->v5.y, b->v5.z,
					b->v6.x, b->v6.y, b->v6.z,

					b->v6.x, b->v6.y, b->v6.z,
					b->v7.x, b->v7.y, b->v7.z,

					b->v7.x, b->v7.y, b->v7.z,
					b->v8.x, b->v8.y, b->v8.z,

					b->v8.x, b->v8.y, b->v8.z,
					b->v5.x, b->v5.y, b->v5.z,

					//Collegamento tra faccia superiore e inferiore:
					b->v1.x, b->v1.y, b->v1.z,
					b->v5.x, b->v5.y, b->v5.z,

					b->v2.x, b->v2.y, b->v2.z,
					b->v6.x, b->v6.y, b->v6.z,

					b->v3.x, b->v3.y, b->v3.z,
					b->v7.x, b->v7.y, b->v7.z,

					b->v4.x, b->v4.y, b->v4.z,
					b->v8.x, b->v8.y, b->v8.z,
				};

				glBindBuffer(GL_ARRAY_BUFFER, idBuff_BoxFrustum);
				glBufferData(GL_ARRAY_BUFFER, SIZE_BUFF_LINES_BOX, nullptr, GL_STREAM_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(arr), arr);

				glUseProgram(shaderColorDebug.getIDShader());
				shaderColorDebug.RenderLines(idBuff_BoxFrustum, glm::vec4(1, 0, 0, 1), glm::mat4(1), camera->getCameraMatrix(), (sizeof(arr) / sizeof(float)) / 3);

				glEnable(GL_DEPTH_TEST);
				#endif
				*/

				lastActor = a;
			}


			delete b; //Disalloco il box

		} //ATTORI

		if (!cullFace) //Nel caso sia disattivato il face culling: lo abilito
			glEnable(GL_CULL_FACE);

		if (lastActor != nullptr) //Se è stato renderizzato almeno un'attore
			DisableArrayShader(lastActor->getModel()->getMaterial()->getShader()); //Disabilito gli array dello shader

		//Applico gli effetti post-process
		ApplayPostRenderEffects(*camera, cameraPortion);

	} //CAMERE

	//Renderizzo l'interfaccia
	RenderUI(S);
}

const RenderingEngineInfo& RenderingEngine::getRenderingEngineInfo() const
{
	return info;
}

GLuint RenderingEngine::getIDBuffUnitQuad()
{
	return idBuffUnitQuad;
}

void RenderingEngine::RenderSkybox(const Skybox* S, const Camera& C)
{
	if (S != nullptr) //Caso ci sia lo skybox per la scena
	{
		//Disabilito il depth test per lo skybox per dare l'impressione che sia molto distante
		glDisable(GL_DEPTH_TEST);
		//Siccome il parametro zNear fornito alla camera può essere alto, disabilito il clipping dei pixel troppo vicini o troppo lontani dalla camera
		//per evitare che i pixel non vengano renderizzati (clipping disabilitato)
		//https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glEnable.xml
		glEnable(GL_DEPTH_CLAMP);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); //Abilito l'interpolazione tra le varie faccie (maggiore qualità sui bordi dello skybox)
		
		//Renderizzo lo skybox:
		glUseProgram(skyboxShader.getIDShader());
		skyboxShader.RenderSkybox(S, C.getCameraMatrix(), C.getPosition());

		//Setto i parametri come prima:
		glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glDisable(GL_DEPTH_CLAMP);
		glEnable(GL_DEPTH_TEST);
	}
}

void RenderingEngine::ApplayPostRenderEffects(const Camera& C, const Rectangle& Portion)
{
	//Disabilito il depth test per impedire che venga utilizzato (scritto) durante le operazioni di post processing
	//il che non avrebbe senso
	glDisable(GL_DEPTH_TEST);

	//Effetti post process
	const std::vector<PostProcessEffect*>* effects = C.getPostProcessEffects();
	int p = 0;
	for (; p < effects->size(); p++) //Ciclo per l'applicazione degli effetti post process
	{
		//Cambio texture in modo alterno per poter renderizzare tutti gli effetti post-process
		//Questa espressione matematica si può tradurre come:
		//if (p % 2 == 0)
		//	camera.changePostProcessRenderTexture(1);
		//else
		//	camera.changePostProcessRenderTexture(0);
		C.changePostProcessRenderTexture(1 - p % 2);
		glClear(GL_COLOR_BUFFER_BIT); //Pulisco la vecchia texture
		PostProcessEffect* eff = (*effects)[p];

		//Settaggio dei parametri di default:
		if (eff->getPostProcessShaderParams() != nullptr) //Caso i parametri ci siano
		{
			eff->getPostProcessShaderParams()->setResolution(glm::vec2(C.getSize().x, C.getSize().y));
		}

		glUseProgram(eff->getPostProcessShader()->getIDShader());
		eff->getPostProcessShader()->ApplayShader(idBuffUnitQuad, C.getRenderedTextureID(p % 2), C.getDepthTextureID(), eff->getPostProcessShaderParams());
	}

	//Rendering su schermo
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(Portion.x, Portion.y, Portion.width, Portion.height); //Re-set del view port
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(postProcess_final.getIDShader());
	postProcess_final.DrawFrame(idBuffUnitQuad, C.getRenderedTextureID(p % 2)); //Renderizzo il frame finale

	glEnable(GL_DEPTH_TEST); //Ri-abilito il delpth test
}

void RenderingEngine::RenderUI(Scene & S)
{
	//Disegno l'interfaccia in 2D
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //Abilito la trasparenza
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	//Diseno gli elementi di interfaccia
	const std::vector<UIElement*> uiElements = S.getUI().getUIElements();
	for (int i = 0; i < uiElements.size(); i++)
		uiElements[i]->DrawControl(&draw2d);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}
