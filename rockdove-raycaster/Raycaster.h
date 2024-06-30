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
	Raycaster(int rows, int columns);

	void OGLRender();

	int GetRows();
	void SetRows(int newRows);

	int	GetColumns();
	void SetColumns(int newColumns);

	float GetHorizonOffset();
	void SetHorizonOffset(float newHorizonOffset);

	

private:
	int m_rows;
	int m_columns;
	float m_horizonOffset;

	void NormalizeHorizonOffset();
};

