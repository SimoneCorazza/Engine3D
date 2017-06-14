#pragma once

/*
File che racchiude metodi di utilità per le textures
*/

#include <GL\glew.h>

//Ottiene la dimensione in byte di un pixel
//[NON TESTATO/CONTROLLATO IN ONGNI CASO]
//@param[in] PixelFormat - Formato di pixel: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA
//@param[in] ComponentType - Indica la tipologia di componenete: GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
//	GL_INT, GL_FLOAT
//@return Dimensione di un pixel in byte
size_t TextureUtils_PixelSize(const GLenum& PixelFormat, const GLenum& ComponentType);