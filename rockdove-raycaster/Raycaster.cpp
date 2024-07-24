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
	SetFieldOfView(90.0f);
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
			glColor3f(0.0f,1.0f,1.0f);
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
	//Render Walls
	float rayDivisionSize = m_fieldOfView / (float)m_columns;

	for (int i = 0; i < m_columns; i++) 
	{
		RayHitResult rayHit = CastRay(Vector2D(1.5, 1.5f), (m_rotation - (m_fieldOfView + (rayDivisionSize * ((float)(i+1))))), 100.0f);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, m_horizonOffset + (0.5f / rayHit.distance));
		glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, m_horizonOffset + (0.5f / rayHit.distance));
		glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, m_horizonOffset - (0.5f / rayHit.distance));
		glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, m_horizonOffset - (0.5f / rayHit.distance));
		glEnd();
	}

	SetRotation(m_rotation + 1);
	CastRay(Vector2D(1.5, 1.5f), m_rotation, 100.0f);
	
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
	Vector2D directionVec = RotToVec(rotation);
	
	if (g_map[(int)initialPosition.x][(int)initialPosition.y] == 1)
	{
		result.bHit = true;
		result.hitPosition = initialPosition;
		result.distance = 0.0f;
		return result;
	}

	//Crude method, can be improved upon, may cause issues with corners
	for (float step = 0.001f; step < maxDistance; step += 0.01f)
	{
		if (g_map[(int)(initialPosition.x + (directionVec.x * (step)))][(int)(initialPosition.y + (directionVec.y * (step)))] == 1) 
		{
			result.bHit = true;
			result.distance = step;
			result.hitPosition = Vector2D(initialPosition.x + (directionVec.x * step), initialPosition.y + (directionVec.y * step));
			break;
		}
	}
	return result;

}


//m_rows
int Raycaster::GetRows() { return m_rows; }
void Raycaster::SetRows(int newRows) { m_rows = newRows; }
//m_columns
int Raycaster::GetColumns() { return m_columns; }
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
	while (newRotation > 360.0f) 
	{
		newRotation -= 360.0f;
	}
	while (newRotation < 0.0f) 
	{
		newRotation += 360.0f;
	}
	m_rotation = newRotation; 
}
//m_fieldOfView
float Raycaster::GetFieldOfView() { return m_fieldOfView; }
void Raycaster::SetFieldOfView(float newFieldOfView) { m_fieldOfView = newFieldOfView; }
