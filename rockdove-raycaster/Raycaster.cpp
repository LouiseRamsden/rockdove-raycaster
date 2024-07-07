#include "Raycaster.h"

#include <math.h>
#include <iostream>

#include "Map.h"

Raycaster::Raycaster(int rows, int columns) 
{
	SetRows(rows);
	SetColumns(columns);
	SetHorizonOffset(0.0f);
	SetViewportPosition(Vector2D(5, 5));
	SetRotation(0.0f);
}

//OpenGl 1.0 Rendering function
void Raycaster::OGLRender() 
{
	static int a = 0;
	a++;

	//Render Sky
	for (int i = 0; i < m_columns; i++)
	{

		glBegin(GL_POLYGON);
		glColor3f((sinf((float)a / 100.0f) + 1.0f) / 2.0f, 1.0f - ((float)i / (float)m_columns), (cosf((float)a / 100) + 1.0f) / 2.0f);
		glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, 1.0f);
		glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, 1.0f);
		glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, m_horizonOffset);
		glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, m_horizonOffset);
		glEnd();
	}
	//Render Floor
	for (int i = 0; i < m_columns; i++)
	{

		glBegin(GL_POLYGON);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, m_horizonOffset);
		glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, m_horizonOffset);
		glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, -1.0f);
		glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, -1.0f);
		glEnd();
	}

	
}
void Raycaster::NormalizeHorizonOffset()
{
	if (m_horizonOffset > 1.0f) 
	{
		m_horizonOffset = 1.0f;
		return;
	}
	if (m_horizonOffset < -1.0f) 
	{
		m_horizonOffset = -1.0f;
		return;
	}
	float step = 2.0f / m_rows;
	float mult = (int)((m_horizonOffset + 1.0f) / step);
	m_horizonOffset = (mult * step) - 1;
}
RayHitResult Raycaster::CastRay(Vector2D initialPosition, float rotation, float maxDistance)
{
	RayHitResult result;
	result.bHit = false;
	Vector2D directionVec;
	directionVec.x = cosf(rotation);
	directionVec.y = sinf(rotation);

	//Rudimentary Method, can be improved
	for (int i = 1; i < 50; i++) 
	{
	}

	return result;

}

//Getters and Setters hall of OOP
//m_rows
uint16_t Raycaster::GetRows() { return m_rows; }
void Raycaster::SetRows(int newRows) { m_rows = newRows; }
//m_columns
uint16_t Raycaster::GetColumns() { return m_columns; }
void Raycaster::SetColumns(int newColumns) { m_columns = newColumns; }
//m_horizonOffset 
float Raycaster::GetHorizonOffset() { return m_horizonOffset; }
void Raycaster::SetHorizonOffset(float newHorizonOffset) 
{ 
	m_horizonOffset = newHorizonOffset; 
	NormalizeHorizonOffset();
}
//m_viewportPosition
Vector2D Raycaster::GetViewportPosition() { return m_viewportPosition; }
void Raycaster::SetViewportPosition(Vector2D newViewportPosition) { m_viewportPosition = newViewportPosition; }
//m_rotation
float Raycaster::GetRotation() { return m_rotation; }
void Raycaster::SetRotation(float newRotation) 
{ 
	if (newRotation > 360.0f) 
	{
		m_rotation = newRotation - 360.0f;
		return;
	}
	if (newRotation < 360.0f) 
	{
		m_rotation = newRotation + 360.0f;
		return;
	}
	m_rotation = newRotation; 
}
//m_fieldOfView
float Raycaster::GetFieldOfView() { return m_fieldOfView; }
void Raycaster::SetFieldOfView(float newFieldOfView) { m_fieldOfView = newFieldOfView; }