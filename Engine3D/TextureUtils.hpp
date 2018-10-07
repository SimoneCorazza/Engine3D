#pragma once

/*
File that includes utility methods for textures
*/

#include <GL\glew.h>

// Gets the size in bytes of a pixel
// [NOT TESTED / CONTROLLED IN ONGNI CASE]
// @param [in] PixelFormat - Pixel format: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA
// @param [in] ComponentType - Indicates the type of components: GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
// GL_INT, GL_FLOAT
// @return Size of a pixel in bytes
size_t TextureUtils_PixelSize(const GLenum& PixelFormat, const GLenum& ComponentType);