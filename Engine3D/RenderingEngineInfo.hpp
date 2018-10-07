#pragma once


// Struct that contains information about the engine
struct RenderingEngineInfo
{
	size_t renderedActors; // Number of actors rendered in the last frame
	size_t renderedTriangles; // Number of rendered triangles
};