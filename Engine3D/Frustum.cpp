#include "Frustum.h"

#include "Box.h"

Frustum::Frustum()
{
}


Frustum::~Frustum()
{
}

void Frustum::setPlanes(const glm::mat4& m)
{
	//Documento per ricavare i piani del frustum culling: http://web.archive.org/web/20120531231005/http://crazyjoke.free.fr/doc/3D/plane%20extraction.pdf
	//Inversione della colonna e della riga rispetto al documento di riferimento (per OpnenGL)

	//Left
	frustum[1].a = m[0][3] + m[0][0];
	frustum[1].b = m[1][3] + m[1][0];
	frustum[1].c = m[2][3] + m[2][0];
	frustum[1].d = m[3][3] + m[3][0];

	//Right
	frustum[0].a = m[0][3] - m[0][0];
	frustum[0].b = m[1][3] - m[1][0];
	frustum[0].c = m[2][3] - m[2][0];
	frustum[0].d = m[3][3] - m[3][0];

	//Top
	frustum[3].a = m[0][3] - m[0][1];
	frustum[3].b = m[1][3] - m[1][1];
	frustum[3].c = m[2][3] - m[2][1];
	frustum[3].d = m[3][3] - m[3][1];

	//Bottom
	frustum[2].a = m[0][3] + m[0][1];
	frustum[2].b = m[1][3] + m[1][1];
	frustum[2].c = m[2][3] + m[2][1];
	frustum[2].d = m[3][3] + m[3][1];

	//Near
	frustum[5].a = m[0][3] + m[0][2];
	frustum[5].b = m[1][3] + m[1][2];
	frustum[5].c = m[2][3] + m[2][2];
	frustum[5].d = m[3][3] + m[3][2];

	//Far
	frustum[4].a = m[0][3] - m[0][2];
	frustum[4].b = m[1][3] - m[1][2];
	frustum[4].c = m[2][3] - m[2][2];
	frustum[4].d = m[3][3] - m[3][2];
}


bool Frustum::TestView(const glm::vec3 & V)
{
	int i = 0;
	while (i < 6 && TestViewPlane(frustum[i], V))
		i++;
	return i == 6;

	/*
	return TestViewPlane(pLeft, V) && TestViewPlane(pRight, V) &&
		TestViewPlane(pTop, V) && TestViewPlane(pBottom, V) &&
		TestViewPlane(pNear, V) && TestViewPlane(pFar, V);
	*/
}


bool Frustum::TestView(const Box* B)
{
	//Per questo metodo è stato utilizzato il codice fornito da: http://www.racer.nl/reference/vfc_markmorley.htm
	//alla sezione "Is This Box In the Frustum?"
	//NOTE:
	//• La normalizzazione dei piani non viene effettuata (vedi ciclo for commentato) e apparentemente funziona lo stesso
	//• In alcuni casi il culling non viene effettuato (ed essendo questo opportuno), tuttativia capita solo in casi sporadici 
	//	e non ben determinati (certe angolazioni o quando si è appena fuori il box)

	/*
	for (int i = 0; i < 8; i++)
		frustum[i].Normalize();
	*/


	for (int p = 0; p < 6; p++)
	{
		if (frustum[p].a * B->v2.x + frustum[p].b * B->v2.y + frustum[p].c * B->v2.z + frustum[p].d > 0)
			continue;
		if (frustum[p].a * B->v3.x + frustum[p].b * B->v3.y + frustum[p].c * B->v3.z + frustum[p].d > 0)
			continue;
		if (frustum[p].a * B->v6.x + frustum[p].b * B->v6.y + frustum[p].c * B->v6.z + frustum[p].d > 0)
			continue;
		if (frustum[p].a * B->v7.x + frustum[p].b * B->v7.y + frustum[p].c * B->v7.z + frustum[p].d > 0)
			continue;
		if (frustum[p].a * B->v1.x + frustum[p].b * B->v1.y + frustum[p].c * B->v1.z + frustum[p].d > 0)
			continue;
		if (frustum[p].a * B->v4.x + frustum[p].b * B->v4.y + frustum[p].c * B->v4.z + frustum[p].d > 0)
			continue;
		if (frustum[p].a * B->v5.x + frustum[p].b * B->v5.y + frustum[p].c * B->v5.z + frustum[p].d > 0)
			continue;
		if (frustum[p].a * B->v8.x + frustum[p].b * B->v8.y + frustum[p].c * B->v8.z + frustum[p].d > 0)
			continue;
		return false;
	}
	return true;

	/*
	//Ritorno false solo se tutti i test falliscono
	return TestView(B->getV1()) || TestView(B->getV2()) ||
		TestView(B->getV3()) || TestView(B->getV4()) ||
		TestView(B->getV5()) || TestView(B->getV6()) ||
		TestView(B->getV7()) || TestView(B->getV8());
	*/
}

bool Frustum::TestView(const glm::vec3 & O, float Radius)
{
	//Per questo metodo è stato utilizzato il codice fornito da: http://www.racer.nl/reference/vfc_markmorley.htm
	//alla sezione "Is This Sphere In the Frustum?"

	for (int p = 0; p < 6; p++)
		if (frustum[p].a * O.x + frustum[p].b * O.y + frustum[p].c * O.z + frustum[p].d <= -Radius)
			return false;
	return true;
}

inline bool Frustum::TestViewPlane(const Plane & P, const glm::vec3 & V)
{
	//Nota questo è dot product tra i due vettori: vec4(P.a, P.b, P.c, P.d) * vec4(V.x, V.y, V.z, 1)
	return P.a * V.x + P.b * V.y + P.c * V.z + P.d >= 0;
}


