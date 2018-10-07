#pragma once

#include <GL\glew.h>
#include <string>

// Number of faces of a cube
#define CUBE_FACES_NUM 6 

// Class that represents a texture cube map
class TextureCube
{
	GLuint idTexture; // ID of the texture

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

		// Gets the ID of the texture cube according to OpenGL
		GLuint getTextureID() const;

		// Gets how the texture is stored in OpenGL
		GLint getInternalFormat() const;

		// Gets the MAX_FILTER of the texturte used
		GLenum getMinFilter() const;
		// Gets the MAX_FILTER of the texturte used
		GLenum getMaxFilter() const;

		// Gets the parameter used for the WARP_S setting of the cube map
		GLint getWrapS() const;
		// Gets the parameter used for the WARP_T setting of the cube map
		GLint getWrapT() const;
		// Gets the parameter used for the WARP_S setting of the cube map
		GLint getWrapR() const;

		// Allows to release the texture
		void Dispose();

		// Allows you to load a textured cube
		// @param [in] FacesPath - Path of 6-sided textures
		// • the faces between them can have different dimensions, but in the same face width = height
		// • the order of the faces is: Right, Left, Top, Bottom, Back, Front
		// @param [in] InternalFormat - Texture storage format
		// @param [in] MinFilter - MIN filter for OpenGL
		// @param [in] MaxFilter - MAX filter for OpenGL
		// @param [in] WrapS - WarpS mode
		// @param [in] WrapT - WarpT mode
		// @param [in] WrapR - WarpR mode
		// @param [in] Usage - Use of the cubemap:
		// True: for internal use, the cube map is created for correct visualization from the inside
		// (NB: in the fragment shader used it is required to invert the X coordinate (x * -1))
		// False: for external use, the cube map is created for correct visualization from the outside
		static TextureCube* NewTextureCube(std::string FacesPath[CUBE_FACES_NUM], GLint InternalFormat, GLenum MinFilter, GLenum MaxFilter, GLint WrapS, GLint WrapT, GLint WrapR, bool Usage);

		// Allows you to load a textured cube
		// @param [in] FacesPath - Path to the texture containing the 6 textures
		// @param [in] InternalFormat - Texture storage format
		// @param [in] MinFilter - MIN filter for OpenGL
		// @param [in] MaxFilter - MAX filter for OpenGL
		// @param [in] WrapS - WarpS mode
		// @param [in] WrapT - WarpT mode
		// @param [in] WrapR - WarpR mode
		// @param [in] Usage - Use of the cubemap:
		// True: for internal use, the cube map is created for correct visualization from the inside
		// (NB: in the fragment shader used it is required to invert the X coordinate (x * -1))
		// False: for external use, the cube map is created for correct visualization from the outside
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

		// Initialize the cubemap
		// @param [in] FacesData - Texture data of the individual faces of the cube:
		// • the faces between them can have different dimensions, but in the same face width = height
		// • the order of the faces is: Right, Left, Top, Bottom, Back, Front
		// @param [in] InternalFormat - Texture storage format
		// @param [in] MinFilter - MIN filter for OpenGL
		// @param [in] MaxFilter - MAX filter for OpenGL
		// @param [in] WrapS - WarpS mode
		// @param [in] WrapT - WarpT mode
		// @param [in] WrapR - WarpR mode
		void Inizialize(Face FacesData[CUBE_FACES_NUM], GLint InternalFormat, GLenum MinFilter, GLenum MaxFilter, GLint WrapS, GLint WrapT, GLint WrapR);
};

