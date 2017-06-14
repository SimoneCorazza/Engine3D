#pragma once

#include <GL\glew.h>

#include "Box.h"

//Classe che rappresenta un'insieme di vertici e di coordinate UV
class Mesh
{
	GLuint idBuffVerteces; //Id del buffer che racchiude i vertici
	GLuint idBuffUV; //ID del buffer che racchiude le coordinate UV
	GLuint idBuffNormals; //ID del buffer contenente le normali

	//int numVertices; //Numero di vertici presenti nella mesh
	int numVerticesDraw; //Numero di vertici da renderizzare separatamente secondo OpenGL
	int sizeInVRAM; //Byte occupati nella VRAM dall'oggetto

	Box frustumBox; //Contenitore per il frustum culling

	private: Mesh();
	public:
		~Mesh();



	public:

		//Ottiene l'ID del buffer dei vertici
		GLuint getIDBuffVerteces() const;

		//Ottiene l'ID del buffer delle UV
		GLuint getIDBuffUV() const;

		//Ottiene l'ID del buffer delle normali (se 0 non presenti)
		GLuint getIDBuffNormals() const;

		//Ottiene il numero di vertici da rendererizzare
		int getVertecesDraw() const;

		//Ottiene la dimensione occupata dalla mesh nella VRAM
		int getSizeInVRAM() const;

		//Ottine il box della Fstrum culling per il modello
		const Box& getFrustumBox() const;

		//Ottiene un flag che indica se la mesh è fornita con le coordinate UV
		const bool hasUV() const;

		//Ottiene un flag che indica se la mesh è fornita con le normali
		const bool hasNormals() const;

		//Consente di eliminare la mesh dalla VRAM
		void Dispose();

		//--- CREAZIONE MESH ---

		//Crea una Mesh
		//@param[in] BuffVerteces - Buffer dei vertici
		//@param[in] BuffUV - Buffer delle UV (null se non presenti)
		//@param[in] BuffNormals - Buffer delle normali (null se non presenti)
		//@param[in] NumVertecesDraw - Numeri di vertici presenti nei vari buffer
		//@param[in] Box - Box che contiene la mesh
		static Mesh* Create(const float* BuffVerteces, const float* BuffUV, const float* BuffNormals, 
			const int& NumVertecesDraw, const Box& Box);

		//Carica una mesh da un file in formato MSH
		//@param[in] Path - Percorso al file
		//@return la mesh contenuta nel file, nullptr nel caso di errore
		static Mesh* LoadMSH(const char* Path);

		//Crea una sfera con l'orientamento dei verici in modo che la faccia sia verso
		//l'esterno della faccia le UV vengono calcolate
		//@param[in] Origin - Origine della sfera
		//@param[in] Radius - Raggio della sfera
		//@param[in] Segments - Numeri di segmenti della sfera (più ce ne sono più la qualità aumenta)
		//		Numeri di quadrilateri = Segments^2 / 2
		//		Deve essere >= 1
		//@param[in] Orentation - Orientamento della sfera:
		//		True:  Vertici e UV vengono calcolati per la sfera in modo da essere visibili dall'interno della sfera
		//		False: Vertici e UV vengono calcolati per la sfera in modo di essere visibili dall'esterno della sfera
		//@param[in] Normals - Indica se generare o meno le normali per la sfera
		//@return Mesh rappresentante la sfera o nullptr se la specifica di Segments non è rispettata
		static Mesh* Sphere(const glm::vec3& Origin, const float& Radius, const int& Segments, const bool& Orentation, const bool& Normals);

		//Crea un cubo senza generare le UV, con le normali delle faccie verso l'interno
		//del cubo (adatto per esembio per uno skybox)
		//@param[in] Origin - Centro del cubo
		//@param[in] Edge - Lato del cubo
		//@return Mesh rappresentate il cubo
		static Mesh* CubeInternal(const glm::vec3& Origin, const float& Edge);
};

