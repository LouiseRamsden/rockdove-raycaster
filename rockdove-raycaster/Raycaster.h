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

#include "Maths.h"


struct RayHitResult 
{
	Vector2D hitPosition;
	float distance;
	bool bHit;

};

class Raycaster
{
public:
	Raycaster(int rows, int columns);

	void OGLRender();

	int GetRows();
	void SetRows(int newRows);

	int GetColumns();
	void SetColumns(int newColumns);

	float GetHorizonOffset();
	void SetHorizonOffset(float newHorizonOffset);

	Vector2D GetViewportPosition();
	void SetViewportPosition(Vector2D newViewportPosition);

	float GetRotation();
	void SetRotation(float newRotation);

	float GetFieldOfView();
	void SetFieldOfView(float newFieldOfView);

private:
	int m_rows;
	int m_columns;
	float m_horizonOffset;
	Vector2D m_viewportPosition;
	float m_rotation;
	float m_fieldOfView;


	void NormalizeHorizonOffset();
	RayHitResult CastRay(Vector2D initialPosition, float rotation, float maxDistance);
};



