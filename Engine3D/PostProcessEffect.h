#pragma once

class PostProcessShader;
class PostProcessShaderParams;

class Camera;

//Classe che racchiude le informazioni  a un effetto post process/rendering
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

		//Consente di rimuovere questo effetto dalla camera
		void RemoveFromCamera();


		//Ottiene l'id di questa istanza di effetto nella camera
		unsigned int getID() const;

		//Ottiene lo shader da usare per questo effetto
		const PostProcessShader* getPostProcessShader() const;

		//Ottiene i parametri per lo shader
		PostProcessShaderParams* getPostProcessShaderParams();
};

