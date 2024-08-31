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

struct Color3
{
	Color3() 
	{
		this->r = 0.0f;
		this->g = 0.0f;
		this->b = 0.0f;
	}
	Color3(float r, float g, float b) 
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
	float r, g, b;
};

struct RayHitResult
{
	Vector2D hitPosition;
	Vector2D rayDirection;
	Color3 rayColor;
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

	float GetDarkness();
	void SetDarkness(const float newDarkness);

	Color3 GetFloorColor();
	void SetFloorColor(Color3 newFloorColor);

	Color3 GetHorizonColor();
	void SetHorizonColor(Color3 newHorizonColor);

	Color3 GetSkyColor();
	void SetSkyColor(Color3 newSkyColor);
	

private:
	int m_rows;
	int m_columns;
	float m_horizonOffset;
	Vector2D m_viewportPosition;
	float m_rotation;
	float m_fieldOfView = 90.0f;
	float m_darkness;
	Color3 m_floorColor;
	Color3 m_horizonColor;
	Color3 m_skyColor;

	float NormalizeToDivisions(float value);
	RayHitResult CastRay(Vector2D initialPosition, float rotation, float maxDistance, float offset);
};
