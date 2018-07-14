#include "Texture2D.h"

#include "DEBUG.h"
#include "TextureDecoder.h"
#include "CommonConstants.h"


Texture2D::Texture2D()
{
	
}

Texture2D::~Texture2D()
{
}






GLuint Texture2D::getIDTexture() const
{
	return idTexture;
}

int Texture2D::getHeight() const
{
	return height;
}

int Texture2D::getWidth() const
{
	return width;
}

GLint Texture2D::getInternalFormat() const
{
	return internalFormat;
}

GLint Texture2D::getWarpS() const
{
	return wrapS;
}

GLint Texture2D::getWarpT() const
{
	return wrapT;
}

GLint Texture2D::getMagFilter() const
{
	return magFilter;
}

GLint Texture2D::getMinFilter() const
{
	return minFilter;
}

GLuint Texture2D::getAnisotropicFilter() const
{
	return anisotropicFilter;
}

void Texture2D::Dispose()
{
	glDeleteTextures(1, &idTexture); // I remove the texture
	width = height = 0;
	idTexture = INVALID_TEXTURE_ID; // Set the ID of the invalid texture
}

Texture2D* Texture2D::NewTexture2D(int Width, int Height, GLvoid * RawData, GLenum DataFormat, GLenum DataType, GLint InternalFormat, GLint WrapS, GLint WrapT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter)
{
	// NOTE: no check on the input

	Texture2D* t = new Texture2D();
	t->InizializeTexture(Width, Height, RawData, DataFormat, DataType, InternalFormat, WrapS, WrapT, MinFilter, MagFilter, AnisotropicFilter);
	return t;
}

Texture2D* Texture2D::NewTexture2D(const std::string & Path, GLint InternalFormat, GLint WrapS, GLint WrapT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter)
{
#ifdef _DEBUG
	Time_Now();
#endif

	int width, height;
	void* data;
	GLenum dataFormat, dataType;
	if (TextureDecoder_DecodeTexture(Path, &data, &dataFormat, &dataType, &width, &height)) // Control how the texture was loaded
	{
		Texture2D* t = new Texture2D();
		t->InizializeTexture(width, height, data, dataFormat, dataType, InternalFormat, WrapS, WrapT, MinFilter, MagFilter, AnisotropicFilter);
		return t;
	}
	else
		return nullptr;

	TextureDecoder_FreeDecode(); // Release the data allocated for the bitmap passed

#ifdef _DEBUG
	TIME_POP("Texture loaded %s", Path.c_str());
#endif
}

void Texture2D::InizializeTexture(int Width, int Height,
	GLvoid* RawData, GLenum DataFormat, GLenum DataType,
	GLint InternalFormat, GLint WrapS, GLint WrapT, GLint MinFilter, GLint MagFilter, GLuint AnisotropicFilter)
{
	glGenTextures(1, &idTexture);
	glBindTexture(GL_TEXTURE_2D, idTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, DataFormat, DataType, RawData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter);

	if (MinFilter != GL_NEAREST && MinFilter != GL_LINEAR) // Check if you need to generate mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLfloat)AnisotropicFilter);

	glBindTexture(GL_TEXTURE_2D, 0); // No texture imposed

	// Set the texture attributes:
	width = Width;
	height = Height;

	internalFormat = InternalFormat;
	wrapS = WrapS;
	wrapT = WrapT;
	minFilter = MinFilter;
	magFilter = MagFilter;
	anisotropicFilter = AnisotropicFilter;
}
