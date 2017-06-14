#pragma once

#include <GL\glew.h>
#include <string>

//Permette di decodificare una texture di un formato supportato (PNG e alcune BMP)
//@param[in] Path - Percorso al file della texture
//@param[out] RawData - Dati della texture (non viene invertito l'ordine delle righr per OpenGL)
//	la disallocazione di essi è commissionata al chiamante mediante delete[]
//@param[out] InternalFormat - Struttura dei dati del colore (GL_RGB, GL_RGBA, ...)
//@param[out] DataType - Tipologia di dato (GL_UNSIGNED_BYTE, GL_FLOAT, ...)
//@param[out] Width - Lunghezza della texture in pixel
//@param[out] Height - ALtezza della texture in pixel
//@return True in caso di succeso false in caso contrario
//@NOTA Quando si ha finito con i dati chiamare il metodo TextureDecoder_FreeDecode() per rilasciarli
bool TextureDecoder_DecodeTexture(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height);

//Permette di rilasciare tutte le bitmap non ancora rilasciate
void TextureDecoder_FreeDecode();

/*
//Permette di decodificare una texture in formato PNG
//@param[in] Path - Percorso al file della texture
//@param[out] RawData - Dati della texture (non viene invertito l'ordine delle righr per OpenGL)
//	la disallocazione di essi è commissionata al chiamante mediante delete[]
//@param[out] InternalFormat - Struttura dei dati del colore (GL_RGB, GL_RGBA, ...)
//@param[out] DataType - Tipologia di dato (GL_UNSIGNED_BYTE, GL_FLOAT, ...)
//@param[out] Width - Lunghezza della texture in pixel
//@param[out] Height - ALtezza della texture in pixel
void TextureDecoder_DecodeTexture_PNG(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height);

//Permette di decodificare una texture in formato BMP
//@param[in] Path - Percorso al file della texture
//@param[out] RawData - Dati della texture (non viene invertito l'ordine delle righr per OpenGL)
//	la disallocazione di essi è commissionata al chiamante mediante delete[]
//@param[out] InternalFormat - Struttura dei dati del colore (GL_RGB, GL_RGBA, ...)
//@param[out] DataType - Tipologia di dato (GL_UNSIGNED_BYTE, GL_FLOAT, ...)
//@param[out] Width - Lunghezza della texture in pixel
//@param[out] Height - ALtezza della texture in pixel
void TextureDecoder_DecodeTexture_BMP(const std::string& Path, GLvoid** RawData, GLenum* DataFormat, GLenum* DataType, int* Width, int* Height);

*/