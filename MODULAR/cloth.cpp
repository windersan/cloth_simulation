#include "cloth.h"
#include <iostream>
#include "vector3.h"

using namespace std;

Cloth::Cloth() {									//set initial positions and masses
	
	

	
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			particlematrix[i][j].Mass = 1;

			particlematrix[i][j].Position0.z = 0;
			particlematrix[i][j].Position0.x = (j) * 0.3;
			particlematrix[i][j].Position0.y = (i) * 0.3;

			particlematrix[i][j].Position = particlematrix[i][j].Position0;
			particlematrix[i][j].Positioni = particlematrix[i][j].Position0;				///Positioni is used to calculate the return length of the spring

			particlematrix[i][j].Velocity0.Zero(); 	
			particlematrix[i][j].Acceleration0.Zero();


			particlematrix[i][j].Force.x = 0;
			particlematrix[i][j].Force.y = 0;
			particlematrix[i][j].Force.z = 0;
			particlematrix[i][j].springforce.x = 0;
			particlematrix[i][j].springforce.y = 0;
			particlematrix[i][j].springforce.z = 0;
			particlematrix[i][j].dampforce.x = 0;
			particlematrix[i][j].dampforce.y = 0;
			particlematrix[i][j].dampforce.z = 0;


		}
	}
	

	for (int i = 0; i < 20; i++) {												//setup triangles
		for (int j = 0; j < 20; j++) {			
			trianglesone[i][j].vrtx1 = particlematrix[i][j].Position;
			trianglesone[i][j].vrtx2 = particlematrix[i + 1][j + 1].Position;
			trianglesone[i][j].vrtx3 = particlematrix[i][j + 1].Position;
					
			trianglestwo[i][j].vrtx1 = particlematrix[i][j].Position;
			trianglestwo[i][j].vrtx2 = particlematrix[i + 1][j + 1].Position;
			trianglestwo[i][j].vrtx3 = particlematrix[i + 1][j].Position;
		}
	}			
}


void Cloth::ComputeSpringForces() {
	/*

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			ComputeIndividualSpring(particlematrix[2 * i + 1][2 * j + 1], particlematrix[2 * i][2 * j]);   /// output = particlematrix[1][1].springforce.x;  //THIS IS 0 ALSO...
			ComputeIndividualSpring(particlematrix[2 * i + 1][2 * j + 1], particlematrix[2 * i][2 * j + 1]);
			ComputeIndividualSpring(particlematrix[2 * i + 1][2 * j + 1], particlematrix[2 * i][2 * j + 2]);
			ComputeIndividualSpring(particlematrix[2 * i + 1][2 * j + 1], particlematrix[2 * i + 1][2 * j]);
			ComputeIndividualSpring(particlematrix[2 * i + 1][2 * j + 1], particlematrix[2 * i + 1][2 * j + 2]);
			ComputeIndividualSpring(particlematrix[2 * i + 1][2 * j + 1], particlematrix[2 * i + 2][2 * j]);
			ComputeIndividualSpring(particlematrix[2 * i + 1][2 * j + 1], particlematrix[2 * i + 2][2 * j + 1]);
			ComputeIndividualSpring(particlematrix[2 * i + 1][2 * j + 1], particlematrix[2 * i + 2][2 * j + 2]);

		}
		
	}
	*/
}


void Cloth::ComputeIndividualSpring(Particle p1, Particle p2) {
	
	Vector3 l0;


	l0.x = p2.Positioni.x - p1.Positioni.x; ///cout << endl << endl << "l0: " << l0.x;
	p2.springforce.x += -ks* (p2.Position.x - p1.Position.x - l0.x);								//signs can be tricky here
	p1.springforce.x += ks* (p2.Position.x - p1.Position.x - l0.x);
	output = particlematrix[1][1].springforce.x;

	l0.y = p2.Positioni.y - p1.Positioni.y;
	p2.springforce.y += -ks* (p2.Position.y - p1.Position.y - l0.y);								//signs can be tricky here
	p1.springforce.y += ks* (p2.Position.y - p1.Position.y - l0.y);

	l0.z = p2.Positioni.z - p1.Positioni.z;
	p2.springforce.z += -ks* (p2.Position.z - p1.Position.z - l0.z);								//signs can be tricky here
	p1.springforce.z += ks* (p2.Position.z - p1.Position.z - l0.z);

	







}





void Cloth::Update(float t) {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			particlematrix[i][j].Acceleration.x = 0;
			particlematrix[i][j].Acceleration.y = -g;											//gravity?
			particlematrix[i][j].Acceleration.z = 0;


		
			if (particlematrix[i][j].Position.y < 0) {


				particlematrix[i][j].Position.z +=    0.8*particlematrix[i][j].Position.y;
				particlematrix[i][j].Position.y = 0;// +0.00; //- particlematrix[i][j].Position.y;
				
				particlematrix[i][j].Acceleration.y = 0;
				particlematrix[i][j].Velocity.y = 0;
				//particlematrix[i][j].Velocity.y += -0.1* particlematrix[i][j].Velocity.y;

				//particlematrix[i][j].Velocity.z += 0.0* particlematrix[i][j].Velocity.y;

			
			}
		}
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			//aero force that varies depending on differences in side lengths (eq. to using stnd method)
			particlematrix[i][j].Acceleration.z += 							//use 0.03 for stable soln with just y
				((particlematrix[i][j+1].Position.x - particlematrix[i][j].Position.x) / (particlematrix[i][j+1].Positioni.x - particlematrix[i][j].Positioni.x))
				* ((particlematrix[i + 1][j].Position.y - particlematrix[i][j].Position.y) / (particlematrix[i + 1][j].Positioni.y - particlematrix[i][j].Positioni.y)) * wind;

			//one coupling, this one for a particle to the right

			particlematrix[i][j + 1].Acceleration.x += -ks * ((particlematrix[i][j + 1].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i][j + 1].Positioni.x - particlematrix[i][j].Positioni.x));
			particlematrix[i][j].Acceleration.x += ks * ((particlematrix[i][j + 1].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i][j + 1].Positioni.x - particlematrix[i][j].Positioni.x));
			particlematrix[i][j + 1].Acceleration.x += -kd * (particlematrix[i][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);
			particlematrix[i][j].Acceleration.x += kd * (particlematrix[i][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);

			particlematrix[i][j + 1].Acceleration.y += -ks * ((particlematrix[i][j + 1].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i][j + 1].Positioni.y - particlematrix[i][j].Positioni.y));
			particlematrix[i][j].Acceleration.y += ks * ((particlematrix[i][j + 1].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i][j + 1].Positioni.y - particlematrix[i][j].Positioni.y));
			particlematrix[i][j + 1].Acceleration.y += -kd * (particlematrix[i][j + 1].Velocity.y - particlematrix[i][j].Velocity.y);
			particlematrix[i][j].Acceleration.y += kd * (particlematrix[i][j + 1].Velocity.y - particlematrix[i][j].Velocity.y);

			particlematrix[i][j + 1].Acceleration.z += -ks * ((particlematrix[i][j + 1].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i][j + 1].Positioni.z - particlematrix[i][j].Positioni.z));
			particlematrix[i][j].Acceleration.z += ks * ((particlematrix[i][j + 1].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i][j + 1].Positioni.z - particlematrix[i][j].Positioni.z));
			particlematrix[i][j + 1].Acceleration.z += -kd * (particlematrix[i][j + 1].Velocity.z - particlematrix[i][j].Velocity.z);
			particlematrix[i][j].Acceleration.z += kd * (particlematrix[i][j + 1].Velocity.z - particlematrix[i][j].Velocity.z);

			//one coupling, this one for a particle above:
			particlematrix[i + 1][j].Acceleration.x +=   -ks * ((particlematrix[i + 1][j].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i + 1][j].Positioni.x - particlematrix[i][j].Positioni.x));
			particlematrix[i][j].Acceleration.x +=   ks * ((particlematrix[i + 1][j].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i + 1][j].Positioni.x - particlematrix[i][j].Positioni.x));
			particlematrix[i + 1][j].Acceleration.x += -kd * (particlematrix[i + 1][j].Velocity.x - particlematrix[i][j].Velocity.x);
			particlematrix[i][j].Acceleration.x += kd * (particlematrix[i + 1][j].Velocity.x - particlematrix[i][j].Velocity.x);

			particlematrix[i + 1][j].Acceleration.y += -ks * ((particlematrix[i + 1][j].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i + 1][j].Positioni.y - particlematrix[i][j].Positioni.y));
			particlematrix[i][j].Acceleration.y += ks * ((particlematrix[i + 1][j].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i + 1][j].Positioni.y - particlematrix[i][j].Positioni.y));
			particlematrix[i + 1][j].Acceleration.y += -kd * (particlematrix[i + 1][j].Velocity.y - particlematrix[i][j].Velocity.y);
			particlematrix[i][j].Acceleration.y += kd * (particlematrix[i + 1][j].Velocity.y - particlematrix[i][j].Velocity.y);

			particlematrix[i + 1][j].Acceleration.z += -ks * ((particlematrix[i + 1][j].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i + 1][j].Positioni.z - particlematrix[i][j].Positioni.z));
			particlematrix[i][j].Acceleration.z += ks * ((particlematrix[i + 1][j].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i + 1][j].Positioni.z - particlematrix[i][j].Positioni.z));
			particlematrix[i + 1][j].Acceleration.z += -kd * (particlematrix[i + 1][j].Velocity.z - particlematrix[i][j].Velocity.z);
			particlematrix[i][j].Acceleration.z += kd * (particlematrix[i + 1][j].Velocity.z - particlematrix[i][j].Velocity.z);



			///crosslinks
			//one coupling, this one for a particle to the right AND above:



			/*particlematrix[i + 1][j + 1].Acceleration.x += -0.1*ks * ((particlematrix[i + 1][j + 1].Position.x - particlematrix[i][j].Position.x) 
				- (particlematrix[i + 1][j + 1].Positioni.x - particlematrix[i][j].Positioni.x)) * ((particlematrix[i + 1][j + 1].Position.x - particlematrix[i][j].Position.x)
					- (particlematrix[i + 1][j + 1].Positioni.x - particlematrix[i][j].Positioni.x));

			particlematrix[i][j].Acceleration.x +=0.1* ks * ((particlematrix[i + 1][j + 1].Position.x - particlematrix[i][j].Position.x)
				- (particlematrix[i + 1][j + 1].Positioni.x - particlematrix[i][j].Positioni.x)) * ((particlematrix[i + 1][j + 1].Position.x - particlematrix[i][j].Position.x)
					- (particlematrix[i + 1][j + 1].Positioni.x - particlematrix[i][j].Positioni.x));

			particlematrix[i + 1][j + 1].Acceleration.x += 1*-kd * (particlematrix[i + 1][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);
			particlematrix[i + 1][j + 1].Acceleration.x += 0.1*  -kd * (particlematrix[i + 1][j + 1].Velocity.x - particlematrix[i][j].Velocity.x)* 
				(particlematrix[i + 1][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);

			particlematrix[i][j].Acceleration.x += 1*kd * (particlematrix[i + 1][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);
			particlematrix[i][j].Acceleration.x +=   .1* kd * (particlematrix[i + 1][j + 1].Velocity.x - particlematrix[i][j].Velocity.x)*
				(particlematrix[i + 1][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);*/


			particlematrix[i + 1][j + 1].Acceleration.x += -ks * ((particlematrix[i + 1][j + 1].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i + 1][j + 1].Positioni.x - particlematrix[i][j].Positioni.x));
			particlematrix[i][j].Acceleration.x += ks * ((particlematrix[i + 1][j + 1].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i + 1][j + 1].Positioni.x - particlematrix[i][j].Positioni.x));
			particlematrix[i + 1][j + 1].Acceleration.x += -kd * (particlematrix[i + 1][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);
			particlematrix[i][j].Acceleration.x += kd * (particlematrix[i + 1][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);

			particlematrix[i + 1][j + 1].Acceleration.y += -ks * ((particlematrix[i + 1][j + 1].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i + 1][j + 1].Positioni.y - particlematrix[i][j].Positioni.y));
			particlematrix[i][j].Acceleration.y += ks * ((particlematrix[i + 1][j + 1].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i + 1][j + 1].Positioni.y - particlematrix[i][j].Positioni.y));
			particlematrix[i + 1][j + 1].Acceleration.y += -kd * (particlematrix[i + 1][j + 1].Velocity.y - particlematrix[i][j].Velocity.y);
			particlematrix[i][j].Acceleration.y += kd * (particlematrix[i + 1][j + 1].Velocity.y - particlematrix[i][j].Velocity.y);

			particlematrix[i + 1][j + 1].Acceleration.z += -ks * ((particlematrix[i + 1][j + 1].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i + 1][j + 1].Positioni.z - particlematrix[i][j].Positioni.z));
			particlematrix[i][j].Acceleration.z += ks * ((particlematrix[i + 1][j + 1].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i + 1][j + 1].Positioni.z - particlematrix[i][j].Positioni.z));
			particlematrix[i + 1][j + 1].Acceleration.z += -kd * (particlematrix[i + 1][j + 1].Velocity.z - particlematrix[i][j].Velocity.z);
			particlematrix[i][j].Acceleration.z += kd * (particlematrix[i + 1][j + 1].Velocity.z - particlematrix[i][j].Velocity.z);

			//one coupling, this one for a particle to the left AND above:
			particlematrix[i + 1][j].Acceleration.x += -ks * ((particlematrix[i + 1][j].Position.x - particlematrix[i][j + 1].Position.x) - (particlematrix[i + 1][j].Positioni.x - particlematrix[i][j + 1].Positioni.x));
			particlematrix[i][j + 1].Acceleration.x += ks * ((particlematrix[i + 1][j].Position.x - particlematrix[i][j + 1].Position.x) - (particlematrix[i + 1][j].Positioni.x - particlematrix[i][j + 1].Positioni.x));
			particlematrix[i + 1][j].Acceleration.x += -kd * (particlematrix[i + 1][j].Velocity.x - particlematrix[i][j + 1].Velocity.x);
			particlematrix[i][j + 1].Acceleration.x += kd * (particlematrix[i + 1][j].Velocity.x - particlematrix[i][j + 1].Velocity.x);

			particlematrix[i + 1][j].Acceleration.y += -ks * ((particlematrix[i + 1][j].Position.y - particlematrix[i][j + 1].Position.y) - (particlematrix[i + 1][j].Positioni.y - particlematrix[i][j + 1].Positioni.y));
			particlematrix[i][j + 1].Acceleration.y += ks * ((particlematrix[i + 1][j].Position.y - particlematrix[i][j + 1].Position.y) - (particlematrix[i + 1][j].Positioni.y - particlematrix[i][j + 1].Positioni.y));
			particlematrix[i + 1][j].Acceleration.y += -kd * (particlematrix[i + 1][j].Velocity.y - particlematrix[i][j + 1].Velocity.y);
			particlematrix[i][j + 1].Acceleration.y += kd * (particlematrix[i + 1][j].Velocity.y - particlematrix[i][j + 1].Velocity.y);

			particlematrix[i + 1][j].Acceleration.z += -ks * ((particlematrix[i + 1][j].Position.z - particlematrix[i][j + 1].Position.z) - (particlematrix[i + 1][j].Positioni.z - particlematrix[i][j + 1].Positioni.z));
			particlematrix[i][j + 1].Acceleration.z += ks * ((particlematrix[i + 1][j].Position.z - particlematrix[i][j + 1].Position.z) - (particlematrix[i + 1][j].Positioni.z - particlematrix[i][j + 1].Positioni.z));
			particlematrix[i + 1][j].Acceleration.z += -kd * (particlematrix[i + 1][j].Velocity.z - particlematrix[i][j + 1].Velocity.z);
			particlematrix[i][j + 1].Acceleration.z += kd * (particlematrix[i + 1][j].Velocity.z - particlematrix[i][j + 1].Velocity.z);



		}
	}

	for (int i = 0; i < 20; i++) {												//finish the right side of cloth
		int j = 20;

		//one coupling, this one for a particle above:
		particlematrix[i + 1][j].Acceleration.x += -ks * ((particlematrix[i + 1][j].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i + 1][j].Positioni.x - particlematrix[i][j].Positioni.x));
		particlematrix[i][j].Acceleration.x += ks * ((particlematrix[i + 1][j].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i + 1][j].Positioni.x - particlematrix[i][j].Positioni.x));
		particlematrix[i + 1][j].Acceleration.x += -kd * (particlematrix[i + 1][j].Velocity.x - particlematrix[i][j].Velocity.x);
		particlematrix[i][j].Acceleration.x += kd * (particlematrix[i + 1][j].Velocity.x - particlematrix[i][j].Velocity.x);

		particlematrix[i + 1][j].Acceleration.y +=   -ks * ((particlematrix[i + 1][j].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i + 1][j].Positioni.y - particlematrix[i][j].Positioni.y));
		particlematrix[i][j].Acceleration.y +=  ks * ((particlematrix[i + 1][j].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i + 1][j].Positioni.y - particlematrix[i][j].Positioni.y));
		particlematrix[i + 1][j].Acceleration.y += -kd * (particlematrix[i + 1][j].Velocity.y - particlematrix[i][j].Velocity.y);
		particlematrix[i][j].Acceleration.y += kd * (particlematrix[i + 1][j].Velocity.y - particlematrix[i][j].Velocity.y);

		particlematrix[i + 1][j].Acceleration.z += -ks * ((particlematrix[i + 1][j].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i + 1][j].Positioni.z - particlematrix[i][j].Positioni.z));
		particlematrix[i][j].Acceleration.z += ks * ((particlematrix[i + 1][j].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i + 1][j].Positioni.z - particlematrix[i][j].Positioni.z));
		particlematrix[i + 1][j].Acceleration.z += -kd * (particlematrix[i + 1][j].Velocity.z - particlematrix[i][j].Velocity.z);
		particlematrix[i][j].Acceleration.z += kd * (particlematrix[i + 1][j].Velocity.z - particlematrix[i][j].Velocity.z);
	}


	for (int j = 0; j < 20; j++) {															///finish the top of cloth

		int i = 20;
		//one coupling, this one for a particle to the right

		particlematrix[i][j + 1].Acceleration.x += -ks * ((particlematrix[i][j + 1].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i][j + 1].Positioni.x - particlematrix[i][j].Positioni.x));
		particlematrix[i][j].Acceleration.x += ks * ((particlematrix[i][j + 1].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i][j + 1].Positioni.x - particlematrix[i][j].Positioni.x));
		particlematrix[i][j + 1].Acceleration.x += -kd * (particlematrix[i][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);
		particlematrix[i][j].Acceleration.x += kd * (particlematrix[i][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);

		particlematrix[i][j + 1].Acceleration.y = -ks * ((particlematrix[i][j + 1].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i][j + 1].Positioni.y - particlematrix[i][j].Positioni.y));
		particlematrix[i][j].Acceleration.y = ks * ((particlematrix[i][j + 1].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i][j + 1].Positioni.y - particlematrix[i][j].Positioni.y));
		particlematrix[i][j + 1].Acceleration.y += -kd * (particlematrix[i][j + 1].Velocity.y - particlematrix[i][j].Velocity.y);
		particlematrix[i][j].Acceleration.y += kd * (particlematrix[i][j + 1].Velocity.y - particlematrix[i][j].Velocity.y);

		particlematrix[i][j + 1].Acceleration.z += -ks * ((particlematrix[i][j + 1].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i][j + 1].Positioni.z - particlematrix[i][j].Positioni.z));
		particlematrix[i][j].Acceleration.z += ks * ((particlematrix[i][j + 1].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i][j + 1].Positioni.z - particlematrix[i][j].Positioni.z));
		particlematrix[i][j + 1].Acceleration.z += -kd * (particlematrix[i][j + 1].Velocity.z - particlematrix[i][j].Velocity.z);
		particlematrix[i][j].Acceleration.z += kd * (particlematrix[i][j + 1].Velocity.z - particlematrix[i][j].Velocity.z);

	}
	//should add some additional springs
	//for (int i = 0; i < 1; i++) {
	//	for (int j = 0; j < 1; j++) {

			//particlematrix[10][0].Acceleration.x += -ks * ((particlematrix[10][0].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i + 10][j].Positioni.x - particlematrix[i][j].Positioni.x));
			//particlematrix[0][0].Acceleration.x += ks * ((particlematrix[i + 10][j].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i + 10][j].Positioni.x - particlematrix[i][j].Positioni.x));
		//	particlematrix[10][0].Acceleration.x += -kd * (particlematrix[i + 10][j].Velocity.x - particlematrix[i][j].Velocity.x);
		//	particlematrix[0][0].Acceleration.x += kd * (particlematrix[i + 10][j].Velocity.x - particlematrix[i][j].Velocity.x);

			//particlematrix[10][0].Acceleration.y += 3 * -ks * ((particlematrix[i + 10][j].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i + 10][j].Positioni.y - particlematrix[i][j].Positioni.y));
			//particlematrix[0][0].Acceleration.y += 3 * ks * ((particlematrix[i + 10][j].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i + 10][j].Positioni.y - particlematrix[i][j].Positioni.y));
		//	particlematrix[10][0].Acceleration.y += -kd * (particlematrix[i + 10][j].Velocity.y - particlematrix[i][j].Velocity.y);
			//particlematrix[0][0].Acceleration.y += kd * (particlematrix[i + 10][j].Velocity.y - particlematrix[i][j].Velocity.y);

			//particlematrix[10][0].Acceleration.z += -ks * ((particlematrix[i + 10][j].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i + 10][j].Positioni.z - particlematrix[i][j].Positioni.z));
			//particlematrix[0][0].Acceleration.z += ks * ((particlematrix[i + 10][j].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i + 10][j].Positioni.z - particlematrix[i][j].Positioni.z));
		//	particlematrix[10][0].Acceleration.z += -kd * (particlematrix[i + 10][j].Velocity.z - particlematrix[i][j].Velocity.z);
			//particlematrix[0][0].Acceleration.z += kd * (particlematrix[i + 10][j].Velocity.z - particlematrix[i][j].Velocity.z);
		//}
	//}

	//for (int j = 0; j < 1; j++) {															

		//int i = 20;
		//one coupling, this one for a particle to the right

		//particlematrix[i][j + 10].Acceleration.x += -ks * ((particlematrix[i][j + 10].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i][j + 10].Positioni.x - particlematrix[i][j].Positioni.x));
		//particlematrix[i][j].Acceleration.x += ks * ((particlematrix[i][j + 10].Position.x - particlematrix[i][j].Position.x) - (particlematrix[i][j + 10].Positioni.x - particlematrix[i][j].Positioni.x));
		//particlematrix[i][j + 10].Acceleration.x += -kd * (particlematrix[i][j + 10].Velocity.x - particlematrix[i][j].Velocity.x);
		//particlematrix[i][j].Acceleration.x += kd * (particlematrix[i][j + 1].Velocity.x - particlematrix[i][j].Velocity.x);

		//particlematrix[i][j + 10].Acceleration.y = -ks * ((particlematrix[i][j + 10].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i][j + 10].Positioni.y - particlematrix[i][j].Positioni.y));
		//particlematrix[i][0].Acceleration.y = ks * ((particlematrix[i][j + 10].Position.y - particlematrix[i][j].Position.y) - (particlematrix[i][j + 10].Positioni.y - particlematrix[i][j].Positioni.y));
		//particlematrix[i][j + 10].Acceleration.y += -kd * (particlematrix[i][j + 10].Velocity.y - particlematrix[i][j].Velocity.y);
		//particlematrix[i][j].Acceleration.y += kd * (particlematrix[i][j + 10].Velocity.y - particlematrix[i][j].Velocity.y);

		//particlematrix[i][j + 10].Acceleration.z += -ks * ((particlematrix[i][j + 10].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i][j + 10].Positioni.z - particlematrix[i][j].Positioni.z));
		//particlematrix[i][j].Acceleration.z += ks * ((particlematrix[i][j + 10].Position.z - particlematrix[i][j].Position.z) - (particlematrix[i][j + 10].Positioni.z - particlematrix[i][j].Positioni.z));
		//particlematrix[i][j + 10].Acceleration.z += -kd * (particlematrix[i][j + 10].Velocity.z - particlematrix[i][j].Velocity.z);
		//particlematrix[i][j].Acceleration.z += kd * (particlematrix[i][j + 10].Velocity.z - particlematrix[i][j].Velocity.z);
	
//}

	///add some more damping, because for some reason I reached the max stable kd value before suitable damping has occurred
	/*particlematrix[0][20].Acceleration.x += -kd * (particlematrix[0][20].Velocity.x - particlematrix[10][20].Velocity.x);
	particlematrix[10][20].Acceleration.x += kd * (particlematrix[0][20].Velocity.x - particlematrix[10][20].Velocity.x);
	
	particlematrix[0][20].Acceleration.y += -kd * (particlematrix[0][20].Velocity.y - particlematrix[10][20].Velocity.y);
	particlematrix[10][20].Acceleration.y += kd * (particlematrix[0][20].Velocity.y - particlematrix[10][20].Velocity.y);
	
	particlematrix[0][20].Acceleration.z += -kd * (particlematrix[0][20].Velocity.z - particlematrix[10][20].Velocity.z);
	particlematrix[10][20].Acceleration.z += kd * (particlematrix[0][20].Velocity.z - particlematrix[10][20].Velocity.z);


	particlematrix[20][20].Acceleration.x += -kd * (particlematrix[20][20].Velocity.x - particlematrix[10][10].Velocity.x);
	particlematrix[10][10].Acceleration.x += kd * (particlematrix[20][20].Velocity.x - particlematrix[10][10].Velocity.x);

	particlematrix[20][20].Acceleration.y += -kd * (particlematrix[20][20].Velocity.y - particlematrix[10][10].Velocity.y);
	particlematrix[10][10].Acceleration.y += kd * (particlematrix[20][20].Velocity.y - particlematrix[10][10].Velocity.y);

	particlematrix[20][20].Acceleration.z += -kd * (particlematrix[20][20].Velocity.z - particlematrix[10][10].Velocity.z);
	particlematrix[10][10].Acceleration.z += kd * (particlematrix[20][20].Velocity.z - particlematrix[10][10].Velocity.z);


	particlematrix[10][20].Acceleration.x += -kd * (particlematrix[10][20].Velocity.x - particlematrix[10][0].Velocity.x);
	particlematrix[10][0].Acceleration.x += kd * (particlematrix[10][20].Velocity.x - particlematrix[10][0].Velocity.x);

	particlematrix[10][20].Acceleration.y += -kd * (particlematrix[10][20].Velocity.y - particlematrix[10][0].Velocity.y);
	particlematrix[10][0].Acceleration.y += kd * (particlematrix[10][20].Velocity.y - particlematrix[10][0].Velocity.y);

	particlematrix[10][20].Acceleration.z += -kd * (particlematrix[10][20].Velocity.z - particlematrix[10][0].Velocity.z);
	particlematrix[10][0].Acceleration.z += kd * (particlematrix[10][20].Velocity.z - particlematrix[10][0].Velocity.z);*/


	/*for (int i = 0; i < 9; i++) {

		particlematrix[ i + 5][10].Acceleration.x += .5*-kd * (particlematrix[i + 5][10].Velocity.x - particlematrix[i + 5][18].Velocity.x);
		particlematrix[i+5][18].Acceleration.x += .5*kd * (particlematrix[i + 5][10].Velocity.x - particlematrix[i + 5][18].Velocity.x);

		for (int j = 0; j < 9; j++) {

			//particlematrix[2*(i+1)][2*(j+1)].Acceleration.x += -ks * ((particlematrix[2 * (i + 1)][2 * (j + 1)].Position.x - particlematrix[2 * i][2 * j].Position.x) - (particlematrix[2 * (i + 1)][2 * (j + 1)].Positioni.x - particlematrix[2 * i][2 * j].Positioni.x));
			//particlematrix[2*i][2*j].Acceleration.x += ks * ((particlematrix[2 * (i + 1)][2 * (j + 1)].Position.x - particlematrix[2 * i][2 * j].Position.x) - (particlematrix[2 * (i + 1)][2 * (j + 1)].Positioni.x - particlematrix[2 * i][2 * j].Positioni.x));
			particlematrix[2 * (i + 1)][2 * (j + 1)].Acceleration.x +=  1*-kd * (particlematrix[2 * (i + 1)][2 * (j + 1)].Velocity.x - particlematrix[2 * i][2 * j].Velocity.x);
			particlematrix[2 * i][2 * j].Acceleration.x += 1*kd * (particlematrix[2 * (i + 1)][2 * (j + 1)].Velocity.x - particlematrix[2 * i][2 * j].Velocity.x);

			//particlematrix[2 * (i + 1)][2 * (j + 1)].Acceleration.y += -ks * ((particlematrix[2 * (i + 1)][2 * (j + 1)].Position.y - particlematrix[2 * i][2 * j].Position.y) - (particlematrix[2 * (i + 1)][2 * (j + 1)].Positioni.y - particlematrix[2 * i][2 * j].Positioni.y));
			//particlematrix[2 * i][2 * j].Acceleration.y += ks * ((particlematrix[2 * (i + 1)][2 * (j + 1)].Position.y - particlematrix[2 * i][2 * j].Position.y) - (particlematrix[2 * (i + 1)][2 * (j + 1)].Positioni.y - particlematrix[2 * i][2 * j].Positioni.y));
			particlematrix[2 * (i + 1)][2 * (j + 1)].Acceleration.y += -kd * (particlematrix[2 * (i + 1)][2 * (j + 1)].Velocity.y - particlematrix[2 * i][2 * j].Velocity.y);
			particlematrix[2 * i][2 * j].Acceleration.y += kd * (particlematrix[2 * (i + 1)][2 * (j + 1)].Velocity.y - particlematrix[2 * i][2 * j].Velocity.y);

			//particlematrix[2 * (i + 1)][2 * (j + 1)].Acceleration.z += -ks * ((particlematrix[2 * (i + 1)][2 * (j + 1)].Position.z - particlematrix[2 * i][2 * j].Position.z) - (particlematrix[2 * (i + 1)][2 * (j + 1)].Positioni.z - particlematrix[2 * i][2 * j].Positioni.z));
			//particlematrix[2 * i][2 * j].Acceleration.z += ks * ((particlematrix[2 * (i + 1)][2 * (j + 1)].Position.z - particlematrix[2 * i][2 * j].Position.z) - (particlematrix[2 * (i + 1)][2 * (j + 1)].Positioni.z - particlematrix[2 * i][2 * j].Positioni.z));
			particlematrix[2 * (i + 1)][2 * (j + 1)].Acceleration.z += -kd * (particlematrix[2 * (i + 1)][2 * (j + 1)].Velocity.z - particlematrix[2 * i][2 * j].Velocity.z);
			particlematrix[2 * i][2 * j].Acceleration.z += kd * (particlematrix[2 * (i + 1)][2 * (j + 1)].Velocity.z - particlematrix[2 * i][2 * j].Velocity.z);
		}
	}*/



	//for (int i = 0; i < 20; i++) {
		//for (int j = 0; j < 20; j++) {

			//if (particlematrix[i][j].Position.y < 0) {
				//particlematrix[i][j].Position.y = 0 - particlematrix[i][j].Position.y;

				//particlematrix[i][j].Velocity.y = -0.5 * particlematrix[i][j].Velocity.y;
			//}



			//}
		//}


/*
	If(r.y < y0
		) {
		r.y = y0 - r.y;
		v.y = -elasticity * v.y;
		v.x = (1 - friction) * v.x; // cheezy
		v.z = (1 - friction) * v.z; // cheezy
	}            */








	
	particlematrix[20][0].Acceleration.x = 0;										//set some endpoints that are fixed to enable stable user control
	particlematrix[20][0].Acceleration.y = 0;
	particlematrix[20][0].Acceleration.z = 0;
	particlematrix[20][20].Acceleration.x = 0;
	particlematrix[20][20].Acceleration.y = 0;
	particlematrix[20][20].Acceleration.z = 0;


	for (int j = 0; j < 21; j++) {													//can fix the whole top layer
		particlematrix[20][j].Acceleration.x = 0;
		particlematrix[20][j].Acceleration.y = 0;
		particlematrix[20][j].Acceleration.z = 0;
	}



	//ComputeSpringForces();

	//output = particlematrix[1][1].springforce.x;						

	



	for (int i = 0; i < 20; i++) {												//update triangles
		for (int j = 0; j < 20; j++) {
			//cout << endl<<"POSITION.Y: "<<particlematrix[i][j].Position.y << endl;
			trianglesone[i][j].vrtx1 = particlematrix[i][j].Position;
			trianglesone[i][j].v1 = particlematrix[i][j].Velocity;

			///cout << endl << "trianglesone[i][j].vrtx1 = particlematrix[i][j].Position: " << trianglesone[i][j].vrtx1.x << "   "
			///	<< trianglesone[i][j].vrtx1.y << "   " << trianglesone[i][j].vrtx1.z << endl << endl;

		///	cout << endl << "trianglesone[i][j].v1 = particlematrix[i][j].Velocity: " << trianglesone[i][j].v1.x << "   "
			///	<< trianglesone[i][j].v1.y << "   " << trianglesone[i][j].v1.z << endl << endl;


			trianglesone[i][j].vrtx2 = particlematrix[i + 1][j + 1].Position;
			trianglesone[i][j].v2 = particlematrix[i][j].Velocity;

			trianglesone[i][j].vrtx3 = particlematrix[i][j + 1].Position;
			trianglesone[i][j].v3 = particlematrix[i][j].Velocity;




			trianglesone[i][j].normalone.Cross((trianglesone[i][j].vrtx2 - trianglesone[i][j].vrtx1), (trianglesone[i][j].vrtx3 - trianglesone[i][j].vrtx1));
			trianglesone[i][j].mag_normalone = trianglesone[i][j].normalone.Mag();
			trianglesone[i][j].normalone_unit = trianglesone[i][j].normalone / trianglesone[i][j].mag_normalone;
				
			


			trianglesone[i][j].v_surface = (trianglesone[i][j].v1 + trianglesone[i][j].v2 + trianglesone[i][j].v3) / 3;
			trianglesone[i][j].v = trianglesone[i][j].v_surface;
			trianglesone[i][j].v.z += wind;
			trianglesone[i][j].v_mag = trianglesone[i][j].v.Mag();

			trianglesone[i][j].v_dot_n = trianglesone[i][j].v.Dot(trianglesone[i][j].normalone_unit);

			trianglesone[i][j].a0 = trianglesone[i][j].mag_normalone * 0.5;


			trianglesone[i][j].a = (trianglesone[i][j].a0 * trianglesone[i][j].v_dot_n) / trianglesone[i][j].v_mag;

			




	
			trianglestwo[i][j].vrtx1 = particlematrix[i][j].Position;
			trianglestwo[i][j].vrtx2 = particlematrix[i + 1][j + 1].Position;
			trianglestwo[i][j].vrtx3 = particlematrix[i + 1][j].Position;

			trianglestwo[i][j].normalone.Cross((trianglestwo[i][j].vrtx2 - trianglestwo[i][j].vrtx1), (trianglestwo[i][j].vrtx3 - trianglestwo[i][j].vrtx1));
			trianglestwo[i][j].mag_normalone = trianglestwo[i][j].normalone.Mag();
			trianglestwo[i][j].normalone_unit = trianglestwo[i][j].normalone / trianglestwo[i][j].mag_normalone;




		/////////	particlematrix[i][j].Acceleration.x += 0.0000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.x;
		///////	particlematrix[i][j].Acceleration.y += 0.00000000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.y;
		////////	particlematrix[i][j].Acceleration.z += 0.0000000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.z;

			//particlematrix[i][j].Acceleration.x += 0.0000000000000000000001* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.x;
			//particlematrix[i][j].Acceleration.y += 0.0000000000000000000001* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.y;
			//particlematrix[i][j].Acceleration.z += 0.0000000000000000000001* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.z;

			//particlematrix[i][j].Acceleration.x += 0.0000000000000000000001* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.x;
			//particlematrix[i][j].Acceleration.y += 0.0000000000000000000001* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.y;
			//particlematrix[i][j].Acceleration.z += 0.0000000000000000000001* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.z;



		}
	}

	for (int i = 0; i < 21; i++) {												
		int j = 20;
	///////	particlematrix[i][20].Acceleration.x += 0.00000000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.x;
	/////	particlematrix[i][20].Acceleration.y += 0.0000000000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.y;
	///////	particlematrix[i][20].Acceleration.z += 0.0000000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.z;

		//cout << endl << "FACTOR: " << trianglestwo[i][j].normalone_unit.x <<endl<<endl;

		//cout <<endl<<"FACTOR: "<< trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.x<<endl<<endl;
	}

	for (int j = 0; j < 20; j++) {												
		int i = 20;
	//////	particlematrix[20][j].Acceleration.x += 0.0000000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.x;
	///////	particlematrix[20][j].Acceleration.y += 0.0000000000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.y;
	/////	particlematrix[20][j].Acceleration.z += 0.000000000000* trianglestwo[i][j].v_mag * trianglestwo[i][j].v_mag * trianglestwo[i][j].a * trianglestwo[i][j].normalone_unit.z;
	}

	

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {

			
			
			///particlematrix[i][j].Force.x = particlematrix[i][j].springforce.x + particlematrix[i][j].dampforce.x;

			///output = particlematrix[i][j].Force.x;


			///particlematrix[i][j].Force.y = (-g * particlematrix[i][j].Mass) + particlematrix[i][j].springforce.y + particlematrix[i][j].dampforce.y;

			///particlematrix[i][j].Force.z = particlematrix[i][j].springforce.z + particlematrix[i][j].dampforce.z;


			///particlematrix[i][j].Acceleration.x = (particlematrix[i][j].Force.x) / (particlematrix[i][j].Mass);
			///particlematrix[i][j].Acceleration.y = (particlematrix[i][j].Force.y) / (particlematrix[i][j].Mass);
			///particlematrix[i][j].Acceleration.z = (particlematrix[i][j].Force.z) / (particlematrix[i][j].Mass);

			particlematrix[i][j].Velocity.x = (t * particlematrix[i][j].Acceleration.x) + particlematrix[i][j].Velocity0.x;
			particlematrix[i][j].Velocity.y = (t * particlematrix[i][j].Acceleration.y) + particlematrix[i][j].Velocity0.y;
			particlematrix[i][j].Velocity.z = (t * particlematrix[i][j].Acceleration.z) + particlematrix[i][j].Velocity0.z;

			particlematrix[i][j].Position.x = (t * particlematrix[i][j].Velocity.x) + particlematrix[i][j].Position0.x;
			particlematrix[i][j].Position.y = (t * particlematrix[i][j].Velocity.y) + particlematrix[i][j].Position0.y;
			particlematrix[i][j].Position.z = (t * particlematrix[i][j].Velocity.z) + particlematrix[i][j].Position0.z;



			//	particlematrix[i][j].Position.x = particlematrix[i][j].Position0.x + t * particlematrix[i][j].Velocity0.x + 0.5 * t * t * particlematrix[i][j].Acceleration0.x;
			//	particlematrix[i][j].Position.y = particlematrix[i][j].Position0.y + t * particlematrix[i][j].Velocity0.y + 0.5 * t * t * particlematrix[i][j].Acceleration0.y;
			//particlematrix[i][j].Position.z = particlematrix[i][j].Position0.z + t * particlematrix[i][j].Velocity0.z + 0.5 * t * t * particlematrix[i][j].Acceleration0.z;


		}
	}







	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			particlematrix[i][j].Acceleration0 = particlematrix[i][j].Acceleration;
			particlematrix[i][j].Velocity0 = particlematrix[i][j].Velocity;
			particlematrix[i][j].Position0 = particlematrix[i][j].Position;
		}
	}


}









void Cloth::Draw() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			trianglesone[i][j].Draw();
			trianglestwo[i][j].Draw();
		}
	}
}


void Cloth::ComputeAeroForces() {




}