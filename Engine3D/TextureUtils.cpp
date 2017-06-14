#include "TextureUtils.h"



size_t TextureUtils_PixelSize(const GLenum& PixelFormat, const GLenum& ComponentType)
{
	size_t componentsNumber; //Numero di componenti
	size_t componentsSize; //Dimensione della singola componente

	switch (PixelFormat)
	{
	case GL_RED: componentsNumber = 1; break;
	case GL_RG: componentsNumber = 2; break;
	case GL_RGB: componentsNumber = 3; break;
	case GL_BGR: componentsNumber = 3; break;
	case GL_RGBA: componentsNumber = 4; break;
	case GL_BGRA: componentsNumber = 4; break;

	default: componentsNumber = 1; break;
	}

	switch (ComponentType)
	{
	case GL_UNSIGNED_BYTE: componentsSize = 1; break;
	case GL_BYTE: componentsSize = 1; break;
	case GL_UNSIGNED_SHORT: componentsSize = 2; break;
	case GL_SHORT: componentsSize = 2; break;
	case GL_UNSIGNED_INT: componentsSize = 4; break;
	case GL_INT: componentsSize = 4; break;
	case GL_FLOAT: componentsSize = 4; break;

	default: componentsSize = 1; break;
	}

	return componentsNumber * componentsSize;
}