#pragma once

#include <glm\glm.hpp>
#include "Plane.h"

class Box;




//Classe che permette di determinare se un punto è dentro lo spazio visibile della camera
class Frustum
{
	//Array dei piani che compongono la frustum culling sono in ordine:
	//Right, Left, Bottom, Top, Far, Near
	Plane frustum[6];

public:
	Frustum();
	~Frustum();


public:

	//Imposta i piani del Fstrum data la camera
	//@param[in] m - Matrice delal camera
	void setPlanes(const glm::mat4& m);

	
	//Testa se il punto indicato rientra nel cono visivo
	//@param[in] V - Punto da testare
	//@return True se il punto è nel campo visivo
	bool TestView(const glm::vec3& V);

	//Testa se il box indicato rientra nel cono visivo
	//@param[in] B - Box da testare
	//@return True se il box è nel campo visivo
	//bool TestView(const Box* B);
	bool TestView(const Box* B);

	//Testa se la sfera è visibile nel cono visivo
	//@param[in] O - Origine della sfera
	//@param[in] Radius - Raggio della sfera
	bool TestView(const glm::vec3& O, float Radius);

private:

	//Indica da che parte del piano si trova il vertice
	//@param[in] P - Piano
	//@param[in] V - Vertice
	//@return True il vertice si trova nella porzione positiva del piano [0, +inf[
	inline bool TestViewPlane(const Plane& P, const glm::vec3& V);
};

