#pragma once

#include <GL\glew.h>
#include <string>

// It allows to decode a texture of a supported format (PNG and some BMP)
// @param [in] Path - Path to the texture file
// @param [out] RawData - Texture data (the righr order for OpenGL is not reversed)
// the disallocation of them is commissioned to the caller by means of delete []
// @param [out] InternalFormat - Color data structure (GL_RGB, GL_RGBA, ...)
// @param [out] DataType - Data type (GL_UNSIGNED_BYTE, GL_FLOAT, ...)
// @param [out] Width - Texture length in pixels
// @param [out] Height - Texture height in pixels
// @return True if successful false otherwise
// @NOTE When you are finished with data, call the TextureDecoder_FreeDecode () method to release it
bool TextureDecoder_DecodeTexture(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height);

// Allows to release all the not yet released bitmaps
void TextureDecoder_FreeDecode();

/*
// It allows to decode a texture in PNG format
// @param [in] Path - Path to the texture file
// @param [out] RawData - Texture data (the righr order for OpenGL is not reversed)
// the disallocation of them is commissioned to the caller by means of delete []
// @param [out] InternalFormat - Color data structure (GL_RGB, GL_RGBA, ...)
// @param [out] DataType - Data type (GL_UNSIGNED_BYTE, GL_FLOAT, ...)
// @param [out] Width - Texture length in pixels
// @param [out] Height - Texture height in pixels
void TextureDecoder_DecodeTexture_PNG(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height);

// It allows to decode a texture in BMP format
// @param [in] Path - Path to the texture file
// @param [out] RawData - Texture data (the righr order for OpenGL is not reversed)
// the disallocation of them is commissioned to the caller by means of delete []
// @param [out] InternalFormat - Color data structure (GL_RGB, GL_RGBA, ...)
// @param [out] DataType - Data type (GL_UNSIGNED_BYTE, GL_FLOAT, ...)
// @param [out] Width - Texture length in pixels
// @param [out] Height - Texture height in pixels
void TextureDecoder_DecodeTexture_BMP(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height);

*/