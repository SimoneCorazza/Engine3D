#pragma once

class Mesh;
class Material;

//Classe che rappresenta un modello di un'oggetto texturizzato
class Model
{
	const Mesh* mesh; //Puntatore alla mesh del modello
	const Material* material; //Puntatore al materiale che compone il modello


	public:
		Model(const Mesh* Mesh, const Material* Material);

		~Model();


	public:

		//Ottiene la mesh del modello
		const Mesh* getMesh() const;

		//Ottiene la texture del modello
		const Material* getMaterial() const;
};

