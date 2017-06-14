#pragma once


//Struct che racchiude le informazioni sull'engine
struct RenderingEngineInfo
{
	size_t renderedActors; //Numero di attori renderizzati nell'ultimo frame
	size_t renderedTriangles; //Numero di triangoli renderizzati
};