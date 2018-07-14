#include "TextureDecoder.h"

#include "DEBUG.h"

// #include "lodepng.h"
// #include "Utility_FileSystem.h"

#include <vector>
#include <FreeImage.h>

std::vector<FIBITMAP*> bitmapCreated; // List of bitmaps created by decoding and not yet released yet to be freed

bool TextureDecoder_DecodeTexture(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height)
{
	// image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib = nullptr; // Bitmap to load

	// check the file signature and deduce its format
	fif = FreeImage_GetFileType(Path.c_str(), 0);
	// if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(Path.c_str());
	// if still unknown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	// check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, Path.c_str());
	// if the image failed to load, return failure
	if (!dib)
		return false;

	// retrieve the image data
	*RawData = FreeImage_GetBits(dib);
	
	// In the case of either 32 or 24 bit forzo having 4 or 3 components regardless of the format of the indicated color
	unsigned int bitPerPixel = FreeImage_GetBPP(dib);
	if (bitPerPixel == 32)
	{
		*DataFormat = GL_BGRA;
		*DataType = GL_UNSIGNED_BYTE;
	}
	else if (bitPerPixel == 24)
	{
		*DataFormat = GL_BGR;
		*DataType = GL_UNSIGNED_BYTE;
	}
	else // Ambiguous format case
	{
		FREE_IMAGE_COLOR_TYPE color = FreeImage_GetColorType(dib);
		switch (color)
		{
		case FREE_IMAGE_COLOR_TYPE::FIC_RGB: *DataFormat = GL_BGR; break;
		case FREE_IMAGE_COLOR_TYPE::FIC_RGBALPHA: *DataFormat = GL_BGRA; break;

		default: *DataFormat = GL_BGR; break;
		}

		*DataType = GL_UNSIGNED_BYTE; // TODO: TO BE IMPROVED IS NOT SAFE
	}
	
	*Width = (int)FreeImage_GetWidth(dib);
	*Height = (int)FreeImage_GetHeight(dib);

	// if this somehow one of these failed (they should not), return failure
	if (*RawData == nullptr || *Height == 0 || *Width == 0)
		return false;

	bitmapCreated.push_back(dib);

	return true;
}

void TextureDecoder_FreeDecode()
{
	for (size_t i = 0; i < bitmapCreated.size(); i++)
		FreeImage_Unload(bitmapCreated[i]);
	bitmapCreated.clear();
}


/*
void TextureDecoder_DecodeTexture(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height)
{
	std::string ext = Utility_FileSystem_GetExtension(Path);
	if (ext == "") // Absent extension case
	{
		Debug_Error("TextureDecoder_DecodeTexture(), estensione assente %s", Path);
		*RawData = nullptr;
		*DataFormat = 0;
		*DataType = 0;
		*Width = 0;
		*Height = 0;
	}
	else if(ext == ".png")
	{
		TextureDecoder_DecodeTexture_PNG(Path, RawData, DataFormat, DataType, Width, Height);
	}
	else if (ext == ".bmp")
	{
		TextureDecoder_DecodeTexture_BMP(Path, RawData, DataFormat, DataType, Width, Height);
	}
	else
	{
		Debug_Error("TextureDecoder_DecodeTexture(), estensione sconosuta %s", Path.c_str());
		*RawData = nullptr;
		*DataFormat = 0;
		*DataType = 0;
		*Width = 0;
		*Height = 0;
	}
}


void TextureDecoder_DecodeTexture_PNG(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height)
{
	std::vector<unsigned char> png;
	lodepng::load_file(png, Path);

	if (png.size() == 0)
	{
		Debug_Error("TextureDecoder_DecodeTexture_PNG(), file vuoto o inesistente %s", Path.c_str());
		*RawData = nullptr;
		*Width = 0;
		*Height = 0;
	}
	else
	{
		std::vector<unsigned char> bitmap;
		unsigned int width, heigth;

		unsigned int error = lodepng::decode(bitmap, width, heigth, png);

		if (error == 0)
		{
			*RawData = new unsigned char[bitmap.size()];
			memcpy(*RawData, &bitmap[0], sizeof(unsigned char) * bitmap.size());
			*DataFormat = GL_RGBA;
			*DataType = GL_UNSIGNED_BYTE;
			*Width = (int)width;
			*Height = (int)heigth;
		}
		else
		{
			Debug_Error("Errore nella decodifica della texture PNG: %s\nErrore: %s", Path.c_str(), lodepng_error_text(error));
			*RawData = nullptr;
			*Width = 0;
			*Height = 0;
		}
	}
}

void TextureDecoder_DecodeTexture_BMP(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height)
{
	Debug_ErrorBreak("TextureDecoder_DecodeTexture_BMP(): Not implemented");
}
*/