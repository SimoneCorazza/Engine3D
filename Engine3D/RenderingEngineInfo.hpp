#pragma once


// Information about the rendered scene
struct RenderingEngineInfo
{
	size_t renderedActors; // Number of actors rendered in the last frame
	size_t renderedTriangles; // Number of rendered triangles
};