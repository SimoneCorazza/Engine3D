#pragma once

class InputState;

//Classe immutabile che raccoglie i parametri da passare alla scena, attori e qualsiasi
//altro elemento da aggiornare
class UpdateParameters
{
	float elapsedTime;
	InputState* inputState;


	public:
		//@param[in] ElapsedTime - Tempo trascorso in secondi dall'ultimo update
		UpdateParameters(float ElapsedTime, InputState* InputState);
		~UpdateParameters();

	public:

		//Ottiene il tempo trascorso in secondi dall'ultimo Update
		float getElapsedTime() const;

		//Ottiene lo stato dell'input attuale
		InputState* getInputState() const;

};

