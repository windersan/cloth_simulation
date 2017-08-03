#include "springdamper.h"
#include <cmath>

void Springdamper::ComputeForce(Particle* P1, Particle* P2, float L0) {

	/*
	l0.x = p2.Positioni.x - p1.Positioni.x;
	p2.springforce.x += -ks* (p2.Position.x - p1.Position.x - l0.x);								
	p1.springforce.x += -p2.springforce.x;

	l0.y = p2.Positioni.y - p1.Positioni.y;
	p2.springforce.y += -ks* (p2.Position.y - p1.Position.y - l0.y);								
	p1.springforce.y += -p2.springforce.y;

	l0.z = p2.Positioni.z - p1.Positioni.z;
	p2.springforce.z += -ks* (p2.Position.z - p1.Position.z - l0.z);								
	p1.springforce.z += -p2.springforce.z;*/



	Vector3 e_un = P2->Position - P1->Position;                     //e unnormalized
	float L = sqrt((e_un.x*e_un.x) + (e_un.y*e_un.y) + (e_un.z*e_un.z));
	Vector3 e = e_un / L;																//e normalized

	float v1f = e.Dot(P1->Velocity);
	float v2f = e.Dot(P2->Velocity);

	float f_sd = -ks * (L0 - L) - kd * (v1f - v2f);


	P1->Force.x = f_sd * e.x;
	P1->Force.y = f_sd * e.y;
	P1->Force.z = f_sd * e.z;
		P2->Force.x = -P1->Force.x;
		P2->Force.y = -P1->Force.y;
		P2->Force.z = -P1->Force.z;
			
}