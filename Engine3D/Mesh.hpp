#pragma once

#include <GL\glew.h>

#include "Box.hpp"

// Class representing a Mesh
class Mesh
{
	// Id of the buffer that encloses the vertices
	GLuint idBuffVerteces;

	// ID of the buffer that encloses the UV coordinates
	GLuint idBuffUV;

	// ID of the buffer containing the normals
	GLuint idBuffNormals;


	// Number of vertices to be rendered separately according to OpenGL
	int numVerticesDraw;
	// Bytes occupied in VRAM by the object
	int sizeInVRAM;

	// Container for frustum culling
	Box frustumBox;

	private: Mesh();
	public:
		~Mesh();



	public:

		// Gets the ID of the vertex buffer
		GLuint getIDBuffVerteces() const;

		// Gets the ID of the UV buffer
		GLuint getIDBuffUV() const;

		// Gets the buffer ID of the normals (if 0 is not present)
		GLuint getIDBuffNormals() const;

		// Gets the number of vertices to be rendered
		int getVertecesDraw() const;

		// Gets the size occupied by the mesh in the VRAM
		int getSizeInVRAM() const;

		// Get the Fstrum culling box for the model
		const Box& getFrustumBox() const;

		// Gets a flag indicating whether the mesh is supplied with the UV coordinates
		const bool hasUV() const;

		// Gets a flag indicating whether the mesh is supplied with normals
		const bool hasNormals() const;

		// Deletes the mesh from the VRAM
		void Dispose();

		// --- MESH CREATION ---

		// Create a Mesh
		// @param[in] BuffVerteces - Vertex buffer
		// @param[in] BuffUV - UV Buffer (null if not present)
		// @param[in] BuffNormals - Normal buffer (null if not present)
		// @param[in] NumVertecesDraw - Numbers of vertices present in the various buffers
		// @param[in] Box - Box containing the mesh
		static Mesh* Create(const float* BuffVerteces, const float* BuffUV, const float* BuffNormals, 
			const int& NumVertecesDraw, const Box& Box);

		// Load a mesh from a file in MSH format
		// @param[in] Path - Path to the file
		// @return the mesh contained in the file, nullptr in case of error
		static Mesh* LoadMSH(const char* Path);

		// Create a sphere with the orientation of the veries so that the face is towards
		// the outside of the face the UV are calculated
		// @param[in] Origin - Origin of the sphere
		// @param[in] Radius - Radius of the sphere
		// @param[in] Segments - Number of segments of the sphere (plus there are more quality increases)
		//		Quadrilaterals numbers = Segments^2 /2
		//		It must be >= 1
		// @param[in] Orientation - Orientation of the sphere:
		//		True: Summits and UV are calculated for the sphere so as to be visible from within the sphere
		//		False: Vertices and UV are calculated for the sphere to be visible from the outside of the sphere
		// @param[in] Normals - Indicates whether or not to generate ball normals
		// @return Mesh representing the sphere or nullptr if the Segments specification is not respected
		static Mesh* Sphere(const glm::vec3& Origin, const float& Radius, const int& Segments, const bool& Orentation, const bool& Normals);

		// Create a cube without generating UV, with the normal faces inward
		// of the cube (suitable for example for a skybox)
		// @param[in] Origin - Center of the cube
		// @param[in] Edge - Side of the cube
		// @return Mesh represent the cube
		static Mesh* CubeInternal(const glm::vec3& Origin, const float& Edge);
};

