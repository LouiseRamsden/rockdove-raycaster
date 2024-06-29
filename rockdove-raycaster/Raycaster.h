/*
* Raycaster:
*	The raycaster itself. Should contain the functionality for actually casting the rays,
*	and even potentially multiple rendering functions for different graphics APIs, may be
*	added to as I learn more APIs throughout uni
*/

#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"


class Raycaster
{
public:
	void OGLRender();

};

