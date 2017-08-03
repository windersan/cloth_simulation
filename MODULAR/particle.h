#pragma once
#include "core.h"
#include "vector3.h"



class Particle {
public:

	Particle();
float Mass; // Constant
Vector3 Position; // Evolves frame to frame
Vector3 Position0;
Vector3 Positioni;					//bookkeeping for our point of oscillation in the spring forces


Vector3 Velocity; // Evolves frame to frame
Vector3 Velocity0;
Vector3 Acceleration;
Vector3 Acceleration0;

Vector3 Force;
Vector3 Force0;
// Reset and re-computed each frame          //refers to the total force?

Vector3 gravity;
Vector3 springforce;
Vector3 dampforce;

public:

	float x0;
	float xf;
	float y0;
	float yf;
	float z0;
	float zf;

	void Update(float deltaTime);
	void Draw();

	//void ApplyForce(Vector3 &f) { Force.Add(f); }

};

