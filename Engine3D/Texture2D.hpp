#pragma once

#include <GL\glew.h>
#include <string>

// Class that contains information related to a 2D texture
class Texture2D
{
	GLuint idTexture; // ID of the texture according to OpenGL

	// Texture size in pixels

	int width;
	int height;

	// Texture information:

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

		// Gets the ID of the texture according to OpenGL
		GLuint getIDTexture() const;

		// Gets the height in pixels of the texture
		int getHeight() const;

		// Gets the length of the texture in pixels
		int getWidth() const;

		// Gets the format of the texture used to store it in OpenGL
		GLint getInternalFormat() const;

		// Gets the setting used for the texture for GL_TEXTURE_WRAP_S
		GLint getWarpS() const;

		// Gets the setting used for the texture for GL_TEXTURE_WRAP_T
		GLint getWarpT() const;

		// Get the texture behavior for the GL_TEXTURE_MAG_FILTER setting
		GLint getMagFilter() const;

		// Get the texture behavior for the GL_TEXTURE_MIN_FILTER setting
		GLint getMinFilter() const;

		// Gets the anisotropic filter used for this texture
		GLuint getAnisotropicFilter() const;

		// Deletes the texture from VRAM
		void Dispose();

		// It allows to load a texture
		// @param [in] Width - Length in textel
		// @param [in] Height - Length in textel
		// @param [in] RawData - Texture data
		// @param [in] DataFormat - Format of data passed in input
		// @param [in] DataType - Type of data
		// @param [in] InternalFormat - Format by which to store the texture in the GPU
		// @param [in] WrapS -
		// @param [in] WrapT -
		// @param [in] MinFilter - MIN Filter
		// @param [in] MagFilter - MAG filter
		// @param [in] AnisotropicFilter - Anisotropic filter to be applied
		// @return Texture loaded; null if there was an error
		static Texture2D* NewTexture2D(int Width, int Height,
			GLvoid* RawData, GLenum DataFormat, GLenum DataType,
			GLint InternalFormat, GLint WrapS, GLint WrapT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter);

		// It allows to load a texture
		// @param [in] Path - Path where to find the texture
		// @param [in] InternalFormat - Format by which to store the texture in the GPU
		// @param [in] WrapS -
		// @param [in] WrapT -
		// @param [in] MinFilter - MIN Filter
		// @param [in] MagFilter - MAG filter
		// @param [in] AnisotropicFilter - Anisotropic filter to be applied
		// @return Texture loaded; null if there was an error loading the file
		static Texture2D* NewTexture2D(const std::string& Path, GLint InternalFormat, GLint WrapS, GLint WrapT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter);

	private:

		// Initializes a texture instance with the indicated data
		// (Texture ID generation performed in this method)
		void InizializeTexture(int Width, int Height,
			GLvoid* RawData, GLenum DataFormat, GLenum DataType,
			GLint InternalFormat, GLint WarpS, GLint WarpT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter);
};

