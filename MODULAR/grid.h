#pragma once
#include "core.h"



void drawGrid(float size, float step)
{
	// disable lighting
	glDisable(GL_LIGHTING);

	// 20x20 grid


	glBegin(GL_POINT);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 3, 3);
	glEnd;


	glBegin(GL_LINES);

	glColor3f(0.5f, 0.5f, 0.5f);
	for (float i = step; i <= size; i += step)
	{
		glVertex3f(-size, 0, i);   // lines parallel to X-axis
		glVertex3f(size, 0, i);
		glVertex3f(-size, 0, -i);   // lines parallel to X-axis
		glVertex3f(size, 0, -i);

		glVertex3f(i, 0, -size);   // lines parallel to Z-axis
		glVertex3f(i, 0, size);
		glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
		glVertex3f(-i, 0, size);
	}

	glColor3f(0, 0, 1);





	// x-axis
	glColor3f(1, 0, 0);
	glVertex3f(-size, 0, 0);
	glVertex3f(size, 0, 0);

	// z-axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -size);
	glVertex3f(0, 0, size);

	glEnd();





	// enable lighting back
	glEnable(GL_LIGHTING);
}

