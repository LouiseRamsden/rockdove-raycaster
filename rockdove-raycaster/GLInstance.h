/*
* GLInstance:
*	Contains all the GLUT functions required for movement and creating a gameloop etc 
*	mainly used because i'm familiar, hopefully built so that I can switch it out for 
*	something else like SDL or GLFW
*/

#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include "Raycaster.h"
#include "Maths.h"
class GLInstance
{
public:
	GLInstance(int argc, char* argv[]);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);
	
	~GLInstance(void);

private:
	Raycaster* m_renderer;
};

