#include "Mesh.h"

#include <vector>

#include <math.h>

#include "BinaryReader.h"
#include "CommonConstants.h"

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
	//Rilascio i buffers:
	glDeleteBuffers(1, &idBuffVerteces);
	glDeleteBuffers(1, &idBuffUV);
	glDeleteBuffers(1, &idBuffNormals);
	//Re-inizializzo i campi associati alla mesh
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

	if (BuffUV == nullptr) //Controllo se le UV sono presenti
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

	if (BuffNormals == nullptr) //Caso normali non inserite
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

//Numero di vertici che compongono la faccia
#define VERTECES_FACE 3

//Consente di caricare un singolo vertice di una faccia
//abbinando a ogni ID il corrispettivo valore che viene aggiunto nel rispettivo array
//@param[in] FaceIndex - Indice della faccia a cui appartiene questo vertice
//@param[in] VertexIndex - Indice del vertice analizzato attualmente (compreso tra 0 e VERTECES_FACE)
//@param[in-out] FacesVerteces - Array dove inserire i dati dei vertici
//@param[in-out] FacesUVs -  Array dove inserire i dati delle UV
//@param[in-out] FacesNormals - Array dove inserire i dati delle normali (se supportate)
//@param[in] Verteces - Array che funge da dizionario per i vari ID dei vertici
//@param[in] UVs - Array che funge da dizionario per i vari ID delle UV
//@param[in] Normals - Array che funge da dizionario per i vari ID delle normali (se supporate)
//@param[in] NormalsSupp - Indica se le normali sono supportate da questa mesh
//@param[in-out] Br - Stream da dove leggere i dati delle faccie
inline void LoadVertexFace(const int& FaceIndex, const int& VertexIndex, float* FacesVerteces, float* FacesUVs, float* FacesNormals,
	float* Verteces, float* UVs, float* Normals, const bool& NormalsSupp, BinaryReader* Br)
{
	//Prendo gli ID degli array da questa faccia:
	int idVerteces = Br->ReadInt32() - 1;
	int idUVs = Br->ReadInt32() - 1;
	int idNormals;
	if (NormalsSupp)
		idNormals = Br->ReadInt32() - 1;
	else
		idNormals = -1;

	//Aggiungo nei rispettivi array i dati:

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
	delete[] signature; //Libero l'array della signature
	if (!isMSHFile) //Caso non abbia la signature
	{
		br.Close();
		return nullptr;
	}

	char normalByte = br.ReadChar();
	bool normSup = normalByte == 1;

	//Dimensioni del box
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

	//Carico i vertici
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

	//Array che contengono i vertici nell'ordine per OpenGL
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

//Ottiene la posizione delle UV della sfera
//@param[in] P - Vertice delle sfera
//@param[in] R - Raggio della sfera
//@param[in] O - Orientamento della coordinata u valori:
//		True:  Visualizza correttamente la texture se si è all'interno della sfera
//		False: Visualizza correttamente la texture se si è all'esterno della sfera
inline glm::vec2 getUVPos(const glm::vec3& P, const float& R, const bool& O)
{
	//FONTE: https://en.wikipedia.org/wiki/UV_mapping
	//Normalizzo le componenti del verrore:
	float nx = P.x / R, ny = P.y / R, nz = P.z / R;
	if (O) //Caso si vogli visualizzare dall'esterno
		std::swap(nz, nx); //Scambio le due coordinate normali
	//Effettuo i calcoli necessari:
	float u = 0.5f + std::atan2(nz, nx) / (2.0f * pi);
	float v =  0.5f - std::asin(ny) / pi;

	return glm::vec2(u, v); //Ritorno il vettore
}

Mesh * Mesh::Sphere(const glm::vec3 & Origin, const float & Radius, const int & Segments, const bool& Orentation, const bool& Normals)
{
	if (Segments <= 0 || Radius == 0)
		return nullptr; //TODO: throw

	const int numVerteces = Segments * Segments / 2 * 6; //Numeri di vertici della sfera
	const int numVertecesSize = numVerteces * 3; //Dimensione in numero di float del buffer dei vertici
	const int numUVSize = numVerteces * 2; //Dimensione in numero di float del buffer delle UV
	GLfloat* verteces = new GLfloat[numVerteces * 3];
	GLfloat* uv = new GLfloat[numVerteces * 2];
	GLfloat* normals = nullptr;
	if(Normals)
		normals = new GLfloat[numVerteces * 3];

	const float interval = (pi * 2.0f) / (float)Segments; //Calcolo l'angolo per i rettangoli

	//Ciclo per disegnare gli anelli della sfera
	for (int counterZ = 0;
	counterZ < Segments / 2; //Eseguo solo una "campana" del seno/coseno
		counterZ++)
	{
		float angleZ = pi + (float)counterZ * interval; //Imposto il nuovo angolo per l'asse Z partendo da 180°

		//Calcolo i due raggi intermedi che seguono l'asse Z (calcolo quello attuale e quello successivo per poterli congiungere)
		//Usati per calcolare l'anello
		float r1 = Radius * sin(angleZ);
		float r2 = Radius * sin(angleZ + interval);

		//Calcolo i due coseni (calcolo quello attuale e quello successivo per poterli congiungere)
		float c1Z = cos(angleZ);
		float c2Z = cos(angleZ + interval);

		//Ciclo per disegnare un anello della sfera sul piano formato con l'asse X e Y
		for (int counterX = 0; counterX < Segments; counterX++)
		{
			float angleX = interval * (float)counterX; //Imposto il nuovo angolo per l'asse X

			float s1 = sin(angleX);
			float c1 = cos(angleX);

			float s2 = sin(angleX + interval);
			float c2 = cos(angleX + interval);

			//Calcolo i quattro vertici del rettangolo
			//Composizione:
			//spostamento sull'asse X del rettangolo (usato il raggio attuale dell'anello);
			//spostamento sull'asse Y del rettangolo (usato il raggio attuale dell'anello);
			//Spostamento sull'asse Z dell'anello
			glm::vec3 v1 = glm::vec3(Origin.x + r1 * s1, Origin.y + r1 * c1, Origin.z + Radius * c1Z);
			glm::vec3 v2 = glm::vec3(Origin.x + r2 * s1, Origin.y + r2 * c1, Origin.z + Radius * c2Z);
			glm::vec3 v3 = glm::vec3(Origin.x + r1 * s2, Origin.y + r1 * c2, Origin.z + Radius * c1Z);
			glm::vec3 v4 = glm::vec3(Origin.x + r2 * s2, Origin.y + r2 * c2, Origin.z + Radius * c2Z);

			if (!Orentation) //Caso si vogla visualizzare la sfera dall'interno
			{
				std::swap(v1, v3);
				std::swap(v2, v4);
			}

			const int vertexStart = (counterZ * Segments + counterX) * 18;
			//Inserisco i vertici del rettangolo (convertiti in due triangoli)
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
			//Inserisco le UV del rettangolo
			uv[uvStart + 0] = uv1.x; uv[uvStart + 1] = uv1.y;
			uv[uvStart + 2] = uv2.x; uv[uvStart + 3] = uv2.y;
			uv[uvStart + 4] = uv3.x; uv[uvStart + 5] = uv3.y;

			uv[uvStart + 6] = uv3.x; uv[uvStart + 7] = uv3.y;
			uv[uvStart + 8] = uv2.x; uv[uvStart + 9] = uv2.y;
			uv[uvStart + 10] = uv4.x; uv[uvStart + 11] = uv4.y;

			//Calcolo la normale di questa faccia (i due triangoli hanno la stessa normale)
			glm::vec3 u = v2 - v1;
			glm::vec3 v = v3 - v1;

			if (Normals)
			{
				//DA SISTEMARE:
				//Array 
				glm::vec3* vertecesVec[6] = 
				{
					&v1, &v2, &v3,
					&v3, &v2, &v4
				};

				const int normalStart = (counterZ * Segments + counterX) * 18;
				for (int i = normalStart, indexVert = 0; i < normalStart + 6 * 3; i += 3, indexVert++)
				{
					//Calcolo la normale dei vertici (http://stackoverflow.com/questions/8024898/calculate-the-vertex-normals-of-a-sphere)
					//della sfera in maniera particolare, siccome è una sfera, rendendole molto più precise
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
	float r = Edge / 2.0f; //Calcolo il raggio del cubo

	//Numero di vertici del cubo (6 faccie, 2 triangoli per faccia, 3 vertici per triangolo)
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
