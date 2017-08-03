#pragma once


#include "vector3.h"
class Triangle {

public:
	void Draw();

	 Vector3 vrtx1;

	 Vector3 vrtx2;

	 Vector3 vrtx3;

	 Vector3 n1;
	 Vector3 n2;
	 Vector3 n3;

	 Vector3 v1;
	 Vector3 v2;
	 Vector3 v3;

	 Vector3 normalone;
	 Vector3 normaltwo;


	 Vector3 normalone_unit;
	 Vector3 normaltwo_unit;

	 float mag_normalone;
	 float mag_normaltwo;

	 float v_dot_n;

	 Vector3 v;
	 Vector3 v_surface;
	 float v_mag;

	 float a0;

	 float a;

	 float cd = 1;
	 Vector3 Normal();

	 Vector3 ComputeAeroForce(Vector3 wind, Vector3 v1, Vector3 v2, Vector3 v3);


};