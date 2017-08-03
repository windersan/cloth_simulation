#include "particle.h"

Particle::Particle() {


	gravity.x = 0;
	gravity.y = Mass * (-0.8);
	gravity.z = 0;


}


void Particle::Update(float deltaTime) {
	// Compute acceleration (Newton’s second law)
	Acceleration = (1 / Mass) * Force;

	
	// Compute new position & velocity
	Velocity += Acceleration * deltaTime;
	Position += Velocity*deltaTime;

	// Zero out Force vector
	Force.Zero();
}