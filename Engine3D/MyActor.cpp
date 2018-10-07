#include "MyActor.hpp"

#include "LiftTriAP.hpp"
#include "UpdateParameters.hpp"
#include "Utility_Time.hpp"

MyActor::MyActor()
{
	param = new LiftTriAP();
}


MyActor::~MyActor()
{
}



void MyActor::Update(const UpdateParameters& P)
{
	LiftTriAP* p = (LiftTriAP*)param;
	p->delta = abs(sinf(Utility_Time_GetTime()));
}
