#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
class GLInstance
{
public:
	GLInstance(int argc, char* argv[]);

	void Display();

	void Update();
	
	~GLInstance(void);
};

