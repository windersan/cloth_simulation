

#ifndef CSE169_CORE_H
#define CSE169_CORE_H



#ifdef WIN32
#define M_PI	3.14159f
#include <windows.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <GL\glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



void drawAxis(float size);
void drawWireBox(float xmin,float ymin,float zmin,float xmax,float ymax,float zmax);



#endif
