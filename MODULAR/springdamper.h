#pragma once
#include "particle.h"



class Springdamper {

	float ks = 1;                     //spring constants for spring force and damping force
	float kd = 1;
	
	
	float L0;			//rest length
	
	float x0;
	float xf;
	float y0;
	float yf;
	float z0;
	float zf;

	
	Particle *P1, *P2;						
	Particle p1, p2;

public:


	void ComputeForce(Particle*, Particle*,float L0);					




};