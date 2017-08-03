#include "triangle.h"
#include "core.h"

void Triangle::Draw() {


	glLoadIdentity();

	glBegin(GL_TRIANGLES);

	glColor3f(1, 0., 0);




	glNormal3f(normalone_unit.x, normalone_unit.y, normalone_unit.z);
	glVertex3f(vrtx1.x,vrtx1.y,vrtx1.z);

	glNormal3f(normalone_unit.x, normalone_unit.y, normalone_unit.z);
	glVertex3f(vrtx2.x,vrtx2.y,vrtx2.z);

	glNormal3f(normalone_unit.x, normalone_unit.y, normalone_unit.z);
	glVertex3f(vrtx3.x, vrtx3.y, vrtx3.z);



	glEnd();
}

Vector3 Triangle::ComputeAeroForce(Vector3 wind, Vector3 v1, Vector3 v2, Vector3 v3) {									

	Vector3 v_surf = (v1 + v2 + v3) / 3;

	Vector3 v = v_surf - wind;

	Vector3 X;
	X.Cross((vrtx2 - vrtx1), (vrtx3 - vrtx1));
	float a0 = sqrt((X.x*X.x) + (X.y*X.y) + (X.z*X.z));
	float a = (a0 * v.Dot(Normal())) / (sqrt(v.x*v.x) + (v.y*v.y) + (v.z*v.z));

	return -cd * a * ((v.x*v.x) + (v.y*v.y) + (v.z*v.z)) * Normal();						//this is the aerodynamic force, will be called by particles

}


Vector3 Triangle::Normal() {

	Vector3 N; 
	N.Cross((vrtx2 - vrtx1), (vrtx3 - vrtx1));
	N.Normalize();
	
	return N;

}