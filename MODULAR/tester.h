


#ifndef CSE169_TESTER_H
#define CSE169_TESTER_H

#include "core.h"
#include "camera.h"
#include "cube.h"

#include <chrono>
#include "cloth.h"

using namespace std;
using namespace std::chrono;


class Tester {
public:
	Tester(int argc,char **argv);
	~Tester();

	void Update();
	void Reset();
	void Draw();

	void Quit();

	// Event handlers
	void Resize(int x,int y);
	void Keyboard(int key,int x,int y);
	void MouseButton(int btn,int state,int x,int y);
	void MouseMotion(int x,int y);

	void showinfo();
	void drawString(const char *str, int x, int y, float color[4], void *font);

	char current[30];


private:
	// Window management
	int WindowHandle;
	int WindowHandle2;
	int WinX,WinY;

	// Input
	bool LeftDown,MiddleDown,RightDown;
	int MouseX,MouseY;

	// Components
	Camera Cam;
	SpinningCube Cube;

	



	float runningt = 0;

	

public:
	
	
	
	 Cloth MyCloth;


	int indx;
	static system_clock::time_point tinit;
	float tt = 0;
	DWORD tick;
};



#endif
