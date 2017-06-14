#pragma once

#include <GL\glew.h>
#include <string>

//Classe che racchiude le informazioni inerenti a una texture 2D
class Texture2D
{
	GLuint idTexture; //ID della texture secondo OpenGL

	//Dimensione della texture in pixel

	int width;
	int height;

	//Informazioni sulla texture:

	GLint internalFormat;
	GLint wrapS;
	GLint wrapT;
	GLint magFilter;
	GLint minFilter;
	GLuint anisotropicFilter;


	private:
		Texture2D();

	public:
		~Texture2D();


	public:

		//Ottiene l'ID della texture secondo OpenGL
		GLuint getIDTexture() const;

		//Ottiene l'altezza in pixel della texture
		int getHeight() const;

		//Ottiene la lunghezza delal texture in pixel
		int getWidth() const;

		//Ottiene il formato della texture usato per memorizzarla in OpenGL
		GLint getInternalFormat() const;

		//Ottiene l'impostazione utilizzata per la texture per GL_TEXTURE_WRAP_S
		GLint getWarpS() const;

		//Ottiene l'impostazione utilizzata per la texture per GL_TEXTURE_WRAP_T
		GLint getWarpT() const;

		//Ottine il comportamento della texture per l'impostazione GL_TEXTURE_MAG_FILTER
		GLint getMagFilter() const;

		//Ottine il comportamento della texture per l'impostazione GL_TEXTURE_MIN_FILTER
		GLint getMinFilter() const;

		//Ottiene il filtro anisotropico usato per questa texture
		GLuint getAnisotropicFilter() const;

		//Consente di eliminare la texture dalla VRAM
		void Dispose();

		//Permette di caricare una texture
		//@param[in] Width - Lunghezza in textel
		//@param[in] Height - Lunghezza in textel
		//@param[in] RawData - Dati della texture
		//@param[in] DataFormat - Formato dei dati passati in input
		//@param[in] DataType - Tipologia dei dati
		//@param[in] InternalFormat - Formato mediante il quale memorizzare la texture nella GPU
		//@param[in] WrapS - 
		//@param[in] WrapT - 
		//@param[in] MinFilter - Filtro MIN
		//@param[in] MagFilter - Filtro MAG
		//@param[in] AnisotropicFilter - Filtro anisotropico da applicare
		//@return Texture caricata; null se c'è stato un errore
		static Texture2D* NewTexture2D(int Width, int Height,
			GLvoid* RawData, GLenum DataFormat, GLenum DataType,
			GLint InternalFormat, GLint WrapS, GLint WrapT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter);

		//Permette di caricare una texture
		//@param[in] Path - Percorso dove trovare la texture
		//@param[in] InternalFormat - Formato mediante il quale memorizzare la texture nella GPU
		//@param[in] WrapS - 
		//@param[in] WrapT - 
		//@param[in] MinFilter - Filtro MIN
		//@param[in] MagFilter - Filtro MAG
		//@param[in] AnisotropicFilter - Filtro anisotropico da applicare
		//@return Texture caricata; null se c'è stato un errore nel caricamento del file
		static Texture2D* NewTexture2D(const std::string& Path, GLint InternalFormat, GLint WrapS, GLint WrapT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter);

	private:

		//Inizializza un istanza di texture con i dati indicati
		//(generazione ID texture effettuata in questo metodo)
		void InizializeTexture(int Width, int Height,
			GLvoid* RawData, GLenum DataFormat, GLenum DataType,
			GLint InternalFormat, GLint WarpS, GLint WarpT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter);
};

