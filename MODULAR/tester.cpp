////////////////////////////////////////
// tester.cpp
////////////////////////////////////////

#include "tester.h"
#include "token.h"
#include <iostream>


#include <vector>
#include "cube.h"
#include "matrix34.h"
#include <cmath>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>

#include <chrono>

#include "windows.h"
#include "grid.h"
#include "cloth.h"


#define WINDOWTITLE	"Spinning Cube"
using namespace std;
using namespace std::chrono;


static Tester *TESTER;





int main(int argc, char **argv) 
{

	

glutInit(&argc, argv);
	TESTER = new Tester(argc, argv);
	
	TESTER->tick = GetTickCount();





glutMainLoop();
	
	


	return 0;
}



															
static void display()									{TESTER->Draw();}
static void idle()										{TESTER->Update();}
static void resize(int x,int y)							{TESTER->Resize(x,y);}
static void keyboard(unsigned char key,int x,int y)		{TESTER->Keyboard(key,x,y);}
static void mousebutton(int btn,int state,int x,int y)	{TESTER->MouseButton(btn,state,x,y);}
static void mousemotion(int x, int y)					{TESTER->MouseMotion(x,y);}




Tester::Tester(int argc, char **argv) {



	WinX=640;
	WinY=480;
	LeftDown=MiddleDown=RightDown=false;
	MouseX=MouseY=0;


	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( WinX, WinY );
	glutInitWindowPosition( 0, 0 );
	WindowHandle = glutCreateWindow( WINDOWTITLE );


	glutSetWindowTitle( WINDOWTITLE );
	glutSetWindow( WindowHandle );


	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.8,3,-1,0.0 };
	GLfloat white_light[] = { 1,0.,0,1.0 };
	GLfloat lmodel_ambient[] = { 0.1,0.4,0.1,1.0 };



	GLfloat light1_ambient[] = { .5,0.0,0.0,1 };  // 0.2,0.2,0.5,1 };
	GLfloat light1_diffuse[] = { 1,1.0,1,1.0 };   //0.5,1.0,0.9,1.0 
	GLfloat light1_specular[] = { 1,1,1,1 };     //{ 0,1,0,1 };
	GLfloat light1_position[] = { -2,-2,1,1 };  // -2,-2,1,1 };
	GLfloat spot_direction[] = { -1,-1,0 };

	
	GLfloat light_position2[] = { 0,-5,0,0.0 };
	GLfloat white_light2[] = { 1,0,0.0,1.0 };

	glClearColor( 0.0, 0., 0.0, 0.0 );                                      //originally at 1

	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


		glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, white_light2);
		
	
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT1);




	glutDisplayFunc( display );
	glutIdleFunc( idle );


	glutKeyboardFunc( keyboard );
	glutMouseFunc( mousebutton );
	glutMotionFunc( mousemotion );
	glutPassiveMotionFunc( mousemotion );
	glutReshapeFunc( resize );




	Cam.SetAspect(float(WinX)/float(WinY));

	
}



Tester::~Tester() {
	glFinish();
	glutDestroyWindow(WindowHandle);
}


float aug = 0;
void Tester::Update() {
	
	
	//int test = tick - GetTickCount();
	//if (test <= 0) {
	//	tick += 12; aug += 0.012;
	//	float ttt = aug;
	
		
		

	//}	
	
	Cam.Update();
	
		MyCloth.Update(0.02);
	

	
		glutSetWindow(WindowHandle);
		glutPostRedisplay();
	
}



void Tester::Reset() {
	Cam.Reset();
	Cam.SetAspect(float(WinX)/float(WinY));

	Cube.Reset();

	

}



void Tester::Draw() {
	glViewport(0, 0, WinX, WinY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	showinfo();


	Cam.Draw();		


	

	MyCloth.Draw();

	drawGrid(10.0f, 1.0f);
	
	
	glFinish();
	glutSwapBuffers();
}



void Tester::Quit() {
	glFinish();
	glutDestroyWindow(WindowHandle);
	exit(0);
}



void Tester::Resize(int x,int y) {
	WinX = x;
	WinY = y;
	Cam.SetAspect(float(WinX)/float(WinY));
}



void Tester::Keyboard(int key,int x,int y) {
	
	switch (key) {
		
		case 0x1b:		// Escape
			Quit();
			break;
		case 'q':
			Reset();
			break;


		case 'a':

			for (int j = 0; j <21; j++)
			{
				MyCloth.particlematrix[20][j].Position.x += -0.1;
				MyCloth.particlematrix[20][j].Position0.x += -0.1;

			}
			break;
		
		case 'd':
		
			for (int j = 0; j <21; j++)
			{
				MyCloth.particlematrix[20][j].Position.x += 0.1;
				MyCloth.particlematrix[20][j].Position0.x += 0.1;

			}
			break;

		case 's':

			for (int j = 0; j <21; j++)
			{
				MyCloth.particlematrix[20][j].Position.y += -0.1;
				MyCloth.particlematrix[20][j].Position0.y += -0.1;

			}
			break;

		case 'w':

			for (int j = 0; j <21; j++)
			{
				MyCloth.particlematrix[20][j].Position.y += 0.1;
				MyCloth.particlematrix[20][j].Position0.y += 0.1;

			}
			break;
		case 'f':

			for (int j = 0; j <21; j++)
			{
				MyCloth.particlematrix[20][j].Position.z += -0.1;
				MyCloth.particlematrix[20][j].Position0.z += -0.1;

			}
			break;

		case 'r':

			for (int j = 0; j <21; j++)
			{
				MyCloth.particlematrix[20][j].Position.z += 0.1;
				MyCloth.particlematrix[20][j].Position0.z += 0.1;

			}
			break;

		case 'b':

			MyCloth.wind -= 0.005;
			
			break;
		case 'v':

			MyCloth.wind += 0.005;

			break;



	}
}



void Tester::MouseButton(int btn,int state,int x,int y) {
	if(btn==GLUT_LEFT_BUTTON) {
		LeftDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_MIDDLE_BUTTON) {
		MiddleDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_RIGHT_BUTTON) {
		RightDown = (state==GLUT_DOWN);
	}
}



void Tester::MouseMotion(int nx,int ny) {
	int dx = nx - MouseX;
	int dy = -(ny - MouseY);

	MouseX = nx;
	MouseY = ny;


	// NOTE: this should really be part of Camera::Update()
	if(LeftDown) {
		const float rate=1.0f;
		Cam.SetAzimuth(Cam.GetAzimuth()+dx*rate);
		Cam.SetIncline(Cam.GetIncline()-dy*rate);
	}
	if(RightDown) {
		const float rate=0.01f;
		Cam.SetDistance(Cam.GetDistance()*(1.0f-dx*rate));
	}
}







void Tester::showinfo()
{

	glPushMatrix();                     // save current modelview matrix
	glLoadIdentity();                   // reset modelview matrix

										// set to 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);        // switch to projection matrix
	glPushMatrix();                     // save current projection matrix
	glLoadIdentity();                   // reset projection matrix
	gluOrtho2D(0, WinX, 0, WinY); // set to orthogonal projection
	


	float color[4] = { 1, 1, 1, 1 };

	

	drawString(current, 0, WinY - 13, color, GLUT_BITMAP_8_BY_13);
	



	// restore projection matrix
	glPopMatrix();                   // restore to previous projection matrix

									 // restore modelview matrix
	glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
	glPopMatrix();                   // restore to previous modelview matrix
}



void Tester::drawString(const char *str, int x, int y, float color[4], void *font)
{
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
	glDisable(GL_TEXTURE_2D);

	glColor4fv(color);          // set text color
	glRasterPos2i(x, y);        // place text position

								// loop all characters in the string
	while (*str)
	{
		glutBitmapCharacter(font, *str);
		++str;
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopAttrib();
}