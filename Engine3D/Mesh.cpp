#include "Mesh.hpp"

#include <vector>

#include <math.h>

#include "BinaryReader.hpp"
#include "CommonConstants.hpp"

Mesh::Mesh()
{
	idBuffVerteces = INVALID_BUFFER_ID;
	idBuffUV = INVALID_BUFFER_ID;
	idBuffNormals = INVALID_BUFFER_ID;

	numVerticesDraw = 0;
	sizeInVRAM = 0;
}


Mesh::~Mesh()
{
}

GLuint Mesh::getIDBuffVerteces() const
{
	return idBuffVerteces;
}

GLuint Mesh::getIDBuffUV() const
{
	return idBuffUV;
}

GLuint Mesh::getIDBuffNormals() const
{
	return idBuffNormals;
}

int Mesh::getVertecesDraw() const
{
	return numVerticesDraw;
}

int Mesh::getSizeInVRAM() const
{
	return sizeInVRAM;
}

const Box & Mesh::getFrustumBox() const
{
	return frustumBox;
}

const bool Mesh::hasUV() const
{
	return idBuffUV != 0;
}

const bool Mesh::hasNormals() const
{
	return idBuffNormals != 0;
}

void Mesh::Dispose()
{
	// Release the buffers:
	glDeleteBuffers(1, &idBuffVerteces);
	glDeleteBuffers(1, &idBuffUV);
	glDeleteBuffers(1, &idBuffNormals);
	// Re-initialize the fields associated with the mesh
	idBuffVerteces = INVALID_BUFFER_ID;
	idBuffUV = INVALID_BUFFER_ID;
	idBuffNormals = INVALID_BUFFER_ID;

	numVerticesDraw = 0;
	sizeInVRAM = 0;
}

Mesh* Mesh::Create(const float* BuffVerteces, const float* BuffUV, const float* BuffNormals, 
	const int& NumVertecesDraw, const Box& Box)
{
	Mesh* m = new Mesh();
	
	int sizeV = NumVertecesDraw * 3 * sizeof(float);
	int sizeUV;
	int sizeNor;

	glGenBuffers(1, &m->idBuffVerteces);
	glBindBuffer(GL_ARRAY_BUFFER, m->idBuffVerteces);
	glBufferData(GL_ARRAY_BUFFER, sizeV, BuffVerteces, GL_STATIC_DRAW);

	// Check if the UVs are present
	if (BuffUV == nullptr)
	{
		m->idBuffUV = 0;
		sizeUV = 0;
	}
	else
	{
		sizeUV = NumVertecesDraw * 2 * sizeof(float);
		glGenBuffers(1, &m->idBuffUV);
		glBindBuffer(GL_ARRAY_BUFFER, m->idBuffUV);
		glBufferData(GL_ARRAY_BUFFER, sizeUV, BuffUV, GL_STATIC_DRAW);
	}

	// Check if the Normals are present
	if (BuffNormals == nullptr)
	{
		m->idBuffNormals = 0;
		sizeNor = 0;
	}
	else
	{
		sizeNor = sizeV;
		glGenBuffers(1, &m->idBuffNormals);
		glBindBuffer(GL_ARRAY_BUFFER, m->idBuffNormals);
		glBufferData(GL_ARRAY_BUFFER, sizeNor, BuffNormals, GL_STATIC_DRAW);
	}

	m->numVerticesDraw = NumVertecesDraw;
	m->sizeInVRAM = sizeV + sizeUV + sizeNor;
	m->frustumBox = Box;

	return m;
}

// Number of vertices that make up the face
#define VERTECES_FACE 3

// Allows you to load a single vertex of a face
// by matching each ID with the corresponding value that is added to the respective array
// @param[in] FaceIndex - Index of the face to which this summit belongs
// @param[in] VertexIndex - Index of the currently analyzed vertex (between 0 and VERTECES_FACE)
// @param[in-out] FacesVerteces - Array where to insert vertex data
// @param[in-out] FacesUVs - Array where to enter UV data
// @param[in-out] FacesNormals - Array where to enter normal data (if supported)
// @param[in] Verteces - Array that serves as a dictionary for the various vertex IDs
// @param[in] UVs - Array that serves as a dictionary for the various UV IDs
// @param[in] Normals - Array that acts as a dictionary for the various IDs of the normals (if supported)
// @param[in] NormalsSupp - Indicates whether normals are supported by this mesh
// @param[in-out] Br - Stream where to read the face data
inline void LoadVertexFace(const int& FaceIndex, const int& VertexIndex, float* FacesVerteces, float* FacesUVs, float* FacesNormals,
	float* Verteces, float* UVs, float* Normals, const bool& NormalsSupp, BinaryReader* Br)
{
	// Take the IDs of the arrays from this face:
	int idVerteces = Br->ReadInt32() - 1;
	int idUVs = Br->ReadInt32() - 1;
	int idNormals;
	if (NormalsSupp)
		idNormals = Br->ReadInt32() - 1;
	else
		idNormals = -1;

	// Add the data in the respective arrays:

	int indexFaceVert = FaceIndex * VERTECES_FACE * 3 + VertexIndex * 3;
	FacesVerteces[indexFaceVert + 0] = Verteces[idVerteces * 3 + 0];
	FacesVerteces[indexFaceVert + 1] = Verteces[idVerteces * 3 + 1];
	FacesVerteces[indexFaceVert + 2] = Verteces[idVerteces * 3 + 2];

	int indexFaceUV = FaceIndex * VERTECES_FACE * 2 + VertexIndex * 2;
	FacesUVs[indexFaceUV + 0] = UVs[idUVs * 2 + 0];
	FacesUVs[indexFaceUV + 1] = UVs[idUVs * 2 + 1];

	if (NormalsSupp)
	{
		int indexFaceNorm = FaceIndex * VERTECES_FACE * 3 + VertexIndex * 3;
		FacesNormals[indexFaceNorm + 0] = Normals[idNormals * 3 + 0];
		FacesNormals[indexFaceNorm + 1] = Normals[idNormals * 3 + 1];
		FacesNormals[indexFaceNorm + 2] = Normals[idNormals * 3 + 2];
	}
}

Mesh* Mesh::LoadMSH(const char* Path)
{
	BinaryReader br(Path);

	if (!br.IsOpen())
	{
		br.Close();
		return nullptr;
	}

	char* signature = br.ReadFixedString(3);
	bool isMSHFile = signature[0] == 'M' && signature[1] == 'S' && signature[2] == 'H';
	delete[] signature;

	// Case does not have the signature
	if (!isMSHFile)
	{
		br.Close();
		return nullptr;
	}

	char normalByte = br.ReadChar();
	bool normSup = normalByte == 1;

	// Box dimensions
	float maxX, maxY, maxZ, minX, minY, minZ;
	maxX = br.ReadSingle();
	minX = br.ReadSingle();
	maxY = br.ReadSingle();
	minY = br.ReadSingle();
	maxZ = br.ReadSingle();
	minZ = br.ReadSingle();

	float* verteces = nullptr;
	float* uvs = nullptr;
	float* normals = nullptr;

	// Load the vertices
	int vertecesCount = br.ReadInt32();
	verteces = new float[vertecesCount * 3];
	for (int i = 0; i < vertecesCount; i++)
	{
		verteces[i * 3 + 0] = br.ReadSingle();
		verteces[i * 3 + 1] = br.ReadSingle();
		verteces[i * 3 + 2] = br.ReadSingle();
	}

	int uvsCount = br.ReadInt32();
	uvs = new float[uvsCount * 3];
	for (int i = 0; i < uvsCount; i++)
	{
		uvs[i * 2 + 0] = br.ReadSingle();
		uvs[i * 2 + 1] = br.ReadSingle();
	}

	int normalsCount;
	if (normSup)
	{
		normalsCount = br.ReadInt32();
		normals = new float[normalsCount * 3];
		for (int i = 0; i < normalsCount; i++)
		{
			normals[i * 3 + 0] = br.ReadSingle();
			normals[i * 3 + 1] = br.ReadSingle();
			normals[i * 3 + 2] = br.ReadSingle();
		}
	}
	else
		normalsCount = 0;

	// Arrays containing vertices in the order for OpenGL
	float* faceVerteces = nullptr;
	float* faceUVs = nullptr;
	float* faceNormals = nullptr;

	int facesCount = br.ReadInt32();
	faceVerteces = new float[facesCount * VERTECES_FACE * 3];
	faceUVs = new float[facesCount * VERTECES_FACE * 2];
	if(normSup)
		faceNormals = new float[facesCount * VERTECES_FACE * 3];
	for (int i = 0; i < facesCount; i++)
	{
		for (int j = 0; j < VERTECES_FACE; j++)
			LoadVertexFace(i, j, faceVerteces, faceUVs, faceNormals, verteces, uvs, normals, normSup, &br);
	}

	br.Close();

	Mesh* msh = Create(faceVerteces, faceUVs, faceNormals, facesCount * VERTECES_FACE, Box(maxX, minX, maxY, minY, maxZ, minZ));
	delete[] verteces;
	delete[] uvs;
	delete[] normals;
	delete[] faceVerteces;
	delete[] faceUVs;
	delete[] faceNormals;
	return msh;
}

#define pi 3.14159265359f

// Gets the position of the UV of the sphere
// @param[in] P - Sphere Summit
// @param[in] R - Sphere of the sphere
// @param[in] O - Coordination orientation u values:
//		True: Display the texture correctly if you are inside the sphere
//		False: Display the texture correctly if you are outside the sphere
inline glm::vec2 getUVPos(const glm::vec3& P, const float& R, const bool& O)
{
	// SOURCE: https://en.wikipedia.org/wiki/UV_mapping
	// I normalize the components of the error:
	float nx = P.x / R, ny = P.y / R, nz = P.z / R;

	// If you want to see from the outside
	if (O)
		std::swap(nz, nx); // Exchange the two normal coordinates
	
	float u = 0.5f + std::atan2(nz, nx) / (2.0f * pi);
	float v =  0.5f - std::asin(ny) / pi;

	return glm::vec2(u, v);
}

Mesh * Mesh::Sphere(const glm::vec3 & Origin, const float & Radius, const int & Segments, const bool& Orentation, const bool& Normals)
{
	if (Segments <= 0 || Radius == 0)
		return nullptr; // TODO: throw

	const int numVerteces = Segments * Segments / 2 * 6; // Numbers of vertices of the sphere
	const int numVertecesSize = numVerteces * 3; // Size in float number of the vertex buffer
	const int numUVSize = numVerteces * 2; // Dimension in number of floats of the UV buffer
	GLfloat* verteces = new GLfloat[numVerteces * 3];
	GLfloat* uv = new GLfloat[numVerteces * 2];
	GLfloat* normals = nullptr;
	if(Normals)
		normals = new GLfloat[numVerteces * 3];

	const float interval = (pi * 2.0f) / (float)Segments; // Calculate the angle for the rectangles

	// Cycle to draw the rings of the sphere
	for (int counterZ = 0;
	counterZ < Segments / 2; // I perform only a "bell" of the sine/cosine
		counterZ++)
	{
		float angleZ = pi + (float)counterZ * interval; // Set the new angle for the Z axis starting from 180°

		// Calculating the two intermediate rays that follow the Z axis (calculate the current one and the next one to be able to join them)
		// Used to calculate the ring
		float r1 = Radius * sin(angleZ);
		float r2 = Radius * sin(angleZ + interval);

		// Calculating the two cosines (calculating the current one and the next one to be able to join them)
		float c1Z = cos(angleZ);
		float c2Z = cos(angleZ + interval);

		// Cycle to draw a ring of the sphere on the plane formed with the X and Y axis
		for (int counterX = 0; counterX < Segments; counterX++)
		{
			float angleX = interval * (float)counterX; // Set the new angle for the X axis

			float s1 = sin(angleX);
			float c1 = cos(angleX);

			float s2 = sin(angleX + interval);
			float c2 = cos(angleX + interval);

			// Calculating the four vertices of the rectangle
			// Composition:
			// movement on the X axis of the rectangle (used the current radius of the ring);
			// movement on the Y axis of the rectangle (used the current radius of the ring);
			// Movement on the Z axis of the ring
			glm::vec3 v1 = glm::vec3(Origin.x + r1 * s1, Origin.y + r1 * c1, Origin.z + Radius * c1Z);
			glm::vec3 v2 = glm::vec3(Origin.x + r2 * s1, Origin.y + r2 * c1, Origin.z + Radius * c2Z);
			glm::vec3 v3 = glm::vec3(Origin.x + r1 * s2, Origin.y + r1 * c2, Origin.z + Radius * c1Z);
			glm::vec3 v4 = glm::vec3(Origin.x + r2 * s2, Origin.y + r2 * c2, Origin.z + Radius * c2Z);

			if (!Orentation) // In case you want to visualize the sphere from the inside
			{
				std::swap(v1, v3);
				std::swap(v2, v4);
			}

			const int vertexStart = (counterZ * Segments + counterX) * 18;
			// Insert the vertices of the rectangle (converted into two triangles)
			verteces[vertexStart + 0] = v1.x; verteces[vertexStart + 1] = v1.y; verteces[vertexStart + 2] = v1.z;
			verteces[vertexStart + 3] = v2.x; verteces[vertexStart + 4] = v2.y; verteces[vertexStart + 5] = v2.z;
			verteces[vertexStart + 6] = v3.x; verteces[vertexStart + 7] = v3.y; verteces[vertexStart + 8] = v3.z;

			verteces[vertexStart + 9] = v3.x; verteces[vertexStart + 10] = v3.y; verteces[vertexStart + 11] = v3.z;
			verteces[vertexStart + 12] = v2.x; verteces[vertexStart + 13] = v2.y; verteces[vertexStart + 14] = v2.z;
			verteces[vertexStart + 15] = v4.x; verteces[vertexStart + 16] = v4.y; verteces[vertexStart + 17] = v4.z;

			glm::vec2 uv1 = getUVPos(v1, Radius, Orentation);
			glm::vec2 uv2 = getUVPos(v2, Radius, Orentation);
			glm::vec2 uv3 = getUVPos(v3, Radius, Orentation);
			glm::vec2 uv4 = getUVPos(v4, Radius, Orentation);

			const int uvStart = (counterZ  * Segments + counterX) * 12;
			// I enter the UV of the rectangle
			uv[uvStart + 0] = uv1.x; uv[uvStart + 1] = uv1.y;
			uv[uvStart + 2] = uv2.x; uv[uvStart + 3] = uv2.y;
			uv[uvStart + 4] = uv3.x; uv[uvStart + 5] = uv3.y;

			uv[uvStart + 6] = uv3.x; uv[uvStart + 7] = uv3.y;
			uv[uvStart + 8] = uv2.x; uv[uvStart + 9] = uv2.y;
			uv[uvStart + 10] = uv4.x; uv[uvStart + 11] = uv4.y;

			// Calculating the normal of this face (the two triangles have the same normal)
			glm::vec3 u = v2 - v1;
			glm::vec3 v = v3 - v1;

			if (Normals)
			{
				// TO Vector:
				// Array
				glm::vec3* vertecesVec[6] = 
				{
					&v1, &v2, &v3,
					&v3, &v2, &v4
				};

				const int normalStart = (counterZ * Segments + counterX) * 18;
				for (int i = normalStart, indexVert = 0; i < normalStart + 6 * 3; i += 3, indexVert++)
				{
					// Calculating the normal of vertices (http://stackoverflow.com/questions/8024898/calculate-the-vertex-normals-of-a-sphere)
					// of the sphere in a particular way, as it is a sphere, making it much more precise
					glm::vec3 n = glm::normalize(*vertecesVec[indexVert] - Origin);

					normals[i + 0] = n.x;
					normals[i + 1] = n.y;
					normals[i + 2] = n.z;
				}
			}
		}
	}

	float diameter = Radius * 2.0f;
	Mesh* mesh = Mesh::Create(verteces, uv, normals, numVerteces, Box(diameter, diameter, diameter));
	delete[] verteces;
	delete[] uv;
	delete[] normals;
	return mesh;
}

Mesh* Mesh::CubeInternal(const glm::vec3& Origin, const float& Edge)
{
	float r = Edge / 2.0f; // Calculate the radius of the cube

	// Number of vertices of the cube (6 faces, 2 triangles per face, 3 vertices per triangle)
	const int numVerteces = 6 * 3 * 2;
	float verteces[numVerteces * 3] =
	{
		Origin.x - r,	Origin.y + r,	Origin.z + r,
		Origin.x - r,	Origin.y - r,	Origin.z + r,
		Origin.x - r,	Origin.y - r,	Origin.z - r,

		Origin.x - r,	Origin.y + r,	Origin.z - r,
		Origin.x - r,	Origin.y - r,	Origin.z - r,
		Origin.x + r,	Origin.y + r,	Origin.z - r,

		Origin.x + r,	Origin.y - r,	Origin.z - r,
		Origin.x - r,	Origin.y - r,	Origin.z - r,
		Origin.x + r,	Origin.y - r,	Origin.z + r,

		Origin.x - r,	Origin.y - r,	Origin.z - r,
		Origin.x + r,	Origin.y - r,	Origin.z - r,
		Origin.x + r,	Origin.y + r,	Origin.z - r,

		Origin.x - r,	Origin.y + r,	Origin.z - r,
		Origin.x - r,	Origin.y + r,	Origin.z + r,
		Origin.x - r,	Origin.y - r,	Origin.z - r,

		Origin.x - r,	Origin.y - r,	Origin.z - r,
		Origin.x - r,	Origin.y - r,	Origin.z + r,
		Origin.x + r,	Origin.y - r,	Origin.z + r,

		Origin.x + r,	Origin.y - r,	Origin.z + r,
		Origin.x - r,	Origin.y - r,	Origin.z + r,
		Origin.x - r,	Origin.y + r,	Origin.z + r,

		Origin.x + r,	Origin.y + r,	Origin.z - r,
		Origin.x + r,	Origin.y - r,	Origin.z - r,
		Origin.x + r,	Origin.y + r,	Origin.z + r,

		Origin.x + r,	Origin.y - r,	Origin.z + r,
		Origin.x + r,	Origin.y + r,	Origin.z + r,
		Origin.x + r,	Origin.y - r,	Origin.z - r,

		Origin.x - r,	Origin.y + r,	Origin.z - r,
		Origin.x + r,	Origin.y + r,	Origin.z - r,
		Origin.x + r,	Origin.y + r,	Origin.z + r,

		Origin.x - r,	Origin.y + r,	Origin.z + r,
		Origin.x - r,	Origin.y + r,	Origin.z - r,
		Origin.x + r,	Origin.y + r,	Origin.z + r,

		Origin.x + r,	Origin.y - r,	Origin.z + r,
		Origin.x - r,	Origin.y + r,	Origin.z + r,
		Origin.x + r,	Origin.y + r,	Origin.z + r,
	};

	Mesh* m = Mesh::Create(verteces, nullptr, nullptr, numVerteces, Box(Origin.x + r, Origin.x - r, Origin.y + r, Origin.y - r, Origin.z + r, Origin.z - r));
	return m;
}
