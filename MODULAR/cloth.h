#pragma once
#include "particle.h"
#include "triangle.h"
#include "springdamper.h"
#include <vector>


using namespace std;

class Cloth {


	float ks = 700;                     //spring constants for spring force and damping force
	float kd = 0.9;

	/////////////////// let's use 0.3 for L0 of non-diag and 0.424264 for L0 of diag
	


public:

	float output;

	Cloth();

	Particle particlematrix[21][21];

	float x0[21];
	float xf[21];
	float y0[21];
	float yf[21];
	float z0[21];
	float zf[21];

	Vector3 windvec;
	float wind = 0.000;
	float g = 0.000;		//grav acceleration 
	
	Triangle trianglesone[20][20];
	Triangle trianglestwo[20][20];

	vector<Triangle> triangles1;
	vector<Triangle> triangles2;

	Vector3 y_hat;


	vector<Springdamper> springdampers;

	void ComputeIndividualSpring(Particle, Particle);
	void ComputeSpringForces();
	void ComputeAeroForces();
	void CollisionDetection();


	void Update(float);
	void Draw();

};