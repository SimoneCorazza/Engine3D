#include "MyLiftTriActor.hpp"

#include "LiftTriAP.hpp"
#include "UpdateParameters.hpp"
#include "Utility_Time.hpp"

MyLiftTriActor::MyLiftTriActor()
{
	param = new LiftTriAP();
}


MyLiftTriActor::~MyLiftTriActor()
{
}

void MyLiftTriActor::Update(const UpdateParameters & P)
{
	LiftTriAP* p = (LiftTriAP*)param;
	p->delta = abs(sinf(Utility_Time_GetTime()));
}
