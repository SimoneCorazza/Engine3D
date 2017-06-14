#include "MyActor.h"

#include "LiftTriAP.h"
#include "UpdateParameters.h"
#include "Utility_Time.h"

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
