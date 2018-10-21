#include "TextureCube.hpp"

#include "TextureDecoder.hpp"
#include "DEBUG.hpp"

#include "Utility_Arrays.hpp"
#include "TextureUtils.hpp"
#include "CommonConstants.hpp"


TextureCube::TextureCube()
{

}

TextureCube::~TextureCube()
{
}






GLuint TextureCube::getTextureID() const
{
	return idTexture;
}

GLint TextureCube::getInternalFormat() const
{
	return internalFormat;
}

GLenum TextureCube::getMinFilter() const
{
	return minFilter;
}

GLenum TextureCube::getMaxFilter() const
{
	return maxFilter;
}

GLint TextureCube::getWrapS() const
{
	return wrapS;
}

GLint TextureCube::getWrapT() const
{
	return wrapT;
}

GLint TextureCube::getWrapR() const
{
	return wrapR;
}

void TextureCube::Dispose()
{
	glDeleteTextures(1, &idTexture);
	idTexture = INVALID_TEXTURE_ID; // Set the texture as invalid
}

// http://learnopengl.com/#!Advanced-OpenGL/Cubemaps
TextureCube * TextureCube::NewTextureCube(std::string FacesPath[CUBE_FACES_NUM], GLint InternalFormat, GLenum MinFilter, GLenum MaxFilter, GLint WrapS, GLint WrapT, GLint WrapR, bool Usage)
{
	if (Usage)
		std::swap(FacesPath[5], FacesPath[4]); // For internal use, I exchange the last two textures

	Face faces[CUBE_FACES_NUM];

	// If true indicates that there was an error loading at least one texture
	bool loadErr = false;

	for (int i = 0; i < CUBE_FACES_NUM && !loadErr; i++)
	{
		int width, height;
		void* data;
		GLenum dataFormat, dataType;
		loadErr |= TextureDecoder_DecodeTexture(FacesPath[i], &data, &dataFormat, &dataType, &width, &height);

		ASSERT(width == height, "TextureCube::TextureCube() to make a MAP CUBE texture width and height of faces must be the same");

		faces[i].width = width;
		faces[i].height = height;
		faces[i].textureData = data;
		faces[i].dataFormat = dataFormat;
		faces[i].dataType = dataType;
	}

	if (loadErr) // There was an error in loading at least one face
		return nullptr;
	else
	{
		TextureCube* t = new TextureCube();
		t->Inizialize(faces, InternalFormat, MinFilter, MaxFilter, WrapS, WrapT, WrapR);
		return t;
	}

	// Disallocate the ram occupied by the textures faces:
	for (int i = 0; i < CUBE_FACES_NUM; i++)
		delete[] faces[i].textureData;
}

TextureCube * TextureCube::NewTextureCube(std::string FacesPath, GLint InternalFormat, GLenum MinFilter, GLenum MaxFilter, GLint WrapS, GLint WrapT, GLint WrapR, bool Usage)
{
	int width, height;
	void* data;
	GLenum dataFormat, dataType;

	if (!TextureDecoder_DecodeTexture(FacesPath, &data, &dataFormat, &dataType, &width, &height)) // Check if there was a loading error
		return nullptr;

	int faceWid = width / 4;
	int faceHei = height / 3;

	size_t sizeTextel = TextureUtils_PixelSize(dataFormat, dataType);


	// Check that the individual frames of the face are equivalent, control it from the same dimension of the texture
	ASSERT(faceWid == faceHei, "TextureCube::TextureCube() to make a MAP CUBE texture width and height of faces must be the same");

	Face faces[CUBE_FACES_NUM];

	void* right = Utility_Arrays_SubMatrix(faceWid * 2, faceHei, faceWid, faceHei, sizeTextel, data, width, height); // right
	void* left = Utility_Arrays_SubMatrix(0, faceHei, faceWid, faceHei, sizeTextel, data, width, height); // left
	void* top = Utility_Arrays_SubMatrix(faceWid, 0, faceWid, faceHei, sizeTextel, data, width, height); // Top
	void* bottom = Utility_Arrays_SubMatrix(faceWid, faceHei * 2, faceWid, faceHei, sizeTextel, data, width, height); // bottom
	void* back = Utility_Arrays_SubMatrix(faceWid * 3, faceHei, faceWid, faceHei, sizeTextel, data, width, height); // back
	void* front = Utility_Arrays_SubMatrix(faceWid, faceHei, faceWid, faceHei, sizeTextel, data, width, height); // front

	if (Usage)
		std::swap(front, back); // For internal use, I exchange the last two textures

	// Set the textures data
	faces[0].textureData = right;
	faces[1].textureData = left;
	faces[2].textureData = top;
	faces[3].textureData = bottom;
	faces[4].textureData = back;
	faces[5].textureData = front;


	for (int i = 0; i < CUBE_FACES_NUM; i++)
	{
		faces[i].width = faceWid;
		faces[i].height = faceHei;
		faces[i].dataFormat = dataFormat;
		faces[i].dataType = dataType;
	}

	TextureCube* t = new TextureCube();
	t->Inizialize(faces, InternalFormat, MinFilter, MaxFilter, WrapS, WrapT, WrapR);

	// Disallocate the ram occupied by the textures faces:
	for (int i = 0; i < CUBE_FACES_NUM; i++)
		delete[] faces[i].textureData;

	return t;
}

void TextureCube::Inizialize(Face FacesData[CUBE_FACES_NUM], GLint InternalFormat, GLenum MinFilter, GLenum MaxFilter, GLint WrapS, GLint WrapT, GLint WrapR)
{
	glGenTextures(1, &idTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, idTexture);

	for (int i = 0; i < CUBE_FACES_NUM; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, InternalFormat, FacesData[i].width, FacesData[i].height, 
			0, FacesData[i].dataFormat, FacesData[i].dataType, FacesData[i].textureData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, MaxFilter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, MinFilter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, WrapS);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, WrapT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, WrapR);

	// I create the mimpmap only if necessary by the filters
	if(MinFilter != GL_NEAREST && MinFilter != GL_LINEAR)
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	internalFormat = InternalFormat;
	minFilter = MinFilter;
	maxFilter = MaxFilter;
	wrapS = WrapS;
	wrapT = WrapT;
	wrapR = WrapR;
}
