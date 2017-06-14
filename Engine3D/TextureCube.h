#pragma once

#include <GL\glew.h>
#include <string>

//Numero di faccie di un cubo
#define CUBE_FACES_NUM 6 

//Classe che rappresenta una texture cube map
class TextureCube
{
	GLuint idTexture; //ID della texture

	GLint internalFormat;
	GLenum minFilter;
	GLenum maxFilter;
	GLint wrapS;
	GLint wrapT;
	GLint wrapR;


	private:
		TextureCube();

	public:
		~TextureCube();


	public:

		//Ottiene l'ID della texture cube secondo OpenGL
		GLuint getTextureID() const;

		//Ottiene come viene memorizzata la texture in OpenGL
		GLint getInternalFormat() const;

		//Ottiene il MAX_FILTER della texturte utilizzato
		GLenum getMinFilter() const;
		//Ottiene il MAX_FILTER della texturte utilizzato
		GLenum getMaxFilter() const;

		//Ottiene il parametro utilizzato per l'impostazione WARP_S della cube map 
		GLint getWrapS() const;
		//Ottiene il parametro utilizzato per l'impostazione WARP_T della cube map 
		GLint getWrapT() const;
		//Ottiene il parametro utilizzato per l'impostazione WARP_S della cube map 
		GLint getWrapR() const;

		//Consente di rilasciare la texture
		void Dispose();

		//Consente di caricare una textured cube
		//@param[in] FacesPath - Path delle texture delle 6 facce
		//	• le faccie tra di loro possono avere dimensioni differenti, ma nella stessa faccia width = height
		//	• l'ordine delle faccie è: Right, Left, Top, Bottom, Back, Front
		//@param[in] InternalFormat - Formato di memorizzazione della texture
		//@param[in] MinFilter - Filtro MIN per OpenGL
		//@param[in] MaxFilter - Filtro MAX per OpenGL
		//@param[in] WrapS - Modalità di WarpS 
		//@param[in] WrapT - Modalità di WarpT
		//@param[in] WrapR - Modalità di WarpR
		//@param[in] Usage - Utilizzo della cubemap:
		//	True: per uso interno, la cube map viene creata per la corretta visualizzazione dall'interno
		//	(NB: nel fragment shader utilizzato si richiede di invertire la coordinata X (x * -1))
		//	False: per uso esterno, la cube map viene creata per la corretta visualizzazione dall'esterno
		static TextureCube* NewTextureCube(std::string FacesPath[CUBE_FACES_NUM], GLint InternalFormat, GLenum MinFilter, GLenum MaxFilter, GLint WrapS, GLint WrapT, GLint WrapR, bool Usage);

		//Consente di caricare una textured cube
		//@param[in] FacesPath - Path alla texture contenente le 6 texture
		//@param[in] InternalFormat - Formato di memorizzazione della texture
		//@param[in] MinFilter - Filtro MIN per OpenGL
		//@param[in] MaxFilter - Filtro MAX per OpenGL
		//@param[in] WrapS - Modalità di WarpS 
		//@param[in] WrapT - Modalità di WarpT
		//@param[in] WrapR - Modalità di WarpR
		//@param[in] Usage - Utilizzo della cubemap:
		//	True: per uso interno, la cube map viene creata per la corretta visualizzazione dall'interno
		//	(NB: nel fragment shader utilizzato si richiede di invertire la coordinata X (x * -1))
		//	False: per uso esterno, la cube map viene creata per la corretta visualizzazione dall'esterno
		static TextureCube* NewTextureCube(std::string FacesPath, GLint InternalFormat, GLenum MinFilter, GLenum MaxFilter, GLint WrapS, GLint WrapT, GLint WrapR, bool Usage);

	private:

		struct Face
		{
			void* textureData;
			int width;
			int height;
			GLint dataFormat;
			GLint dataType;
		};

		//Inizializza la cubemap
		//@param[in] FacesData - Dati delle texture delle singole faccie del cubo:
		//	•le faccie tra di loro possono avere dimensioni differenti, ma nella stessa faccia width = height
		//	•l'ordine delle faccie è: Right, Left, Top, Bottom, Back, Front
		//@param[in] InternalFormat - Formato di memorizzazione della texture
		//@param[in] MinFilter - Filtro MIN per OpenGL
		//@param[in] MaxFilter - Filtro MAX per OpenGL
		//@param[in] WrapS - Modalità di WarpS 
		//@param[in] WrapT - Modalità di WarpT
		//@param[in] WrapR - Modalità di WarpR
		void Inizialize(Face FacesData[CUBE_FACES_NUM], GLint InternalFormat, GLenum MinFilter, GLenum MaxFilter, GLint WrapS, GLint WrapT, GLint WrapR);
};

