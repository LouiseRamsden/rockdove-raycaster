#include "Raycaster.h"

#include <math.h>
#include <iostream>

#include "Map.h"


Raycaster::Raycaster(int rows, int columns) 
{
	SetRows(rows);
	SetColumns(columns);
	SetHorizonOffset(0.0f);
	SetViewportPosition(Vector2D(1.5, 1.5));
	SetRotation(0.0f);
}

//OpenGl 1.0 Rendering function
void Raycaster::OGLRender() 
{
	//Render Sky
	for (int i = 0; i < m_columns; i++)
	{

		glBegin(GL_POLYGON);
			glColor3f(0.03f/2,0.26f/2,0.47f/2);
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, 1.0f);
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, 1.0f);
			glColor3f(0.98f/2, 0.30f/2, 0.15f/2);
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, m_horizonOffset);
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, m_horizonOffset);
		glEnd();
	}
	//Render Floor
	for (int i = 0; i < m_columns; i++)
	{

		glBegin(GL_POLYGON);
			glColor3f(0.0f/3,0.2f/3,0.13f/3);
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, m_horizonOffset);
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, m_horizonOffset);
			glColor3f(0.0f/2, 0.2f/2, 0.13f/2); // Shadows are half brightness at the bottom, can probably make variable
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, -1.0f);
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, -1.0f);
		glEnd();
	}

	//Render Walls
	float rayDivisionSize = m_fieldOfView / (float)m_columns;
	for (int i = 0; i < m_columns; i++) 
	{
		RayHitResult rayHit = CastRay(m_viewportPosition, (m_rotation - (m_fieldOfView + (rayDivisionSize * ((float)(i+1)))) - 45.0f), 20.0f);
		float heightModifier = (1.0f / (rayHit.distance * 2));
		glBegin(GL_POLYGON);
			glColor3f(rayHit.rayColor.r/2, rayHit.rayColor.g/2, rayHit.rayColor.b/2);
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, NormalizeToDivisions(m_horizonOffset + heightModifier));
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, NormalizeToDivisions(m_horizonOffset + heightModifier));
			glColor3f(rayHit.rayColor.r /4 , rayHit.rayColor.g / 4, rayHit.rayColor.b / 4); // Half brightness shadows
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, NormalizeToDivisions(m_horizonOffset - heightModifier));
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, NormalizeToDivisions(m_horizonOffset - heightModifier));
		glEnd();
	}
	
}




float Raycaster::NormalizeToDivisions(float value) 
{
	if (value > 1.0f)
	{
		return 1.0f;
	}
	if (value < -1.0f)
	{
		return -1.0f;
	}
	float step = 2.0f / m_rows;
	float mult = (int)((value + 1.0f) / step);
	return (mult * step) - 1.0f;
}
RayHitResult Raycaster::CastRay(Vector2D initialPosition, float rotation, float maxDistance)
{
	RayHitResult result;
	result.bHit = false;
	Vector2D directionVec = RotToVec(rotation);
	result.rayDirection = directionVec;
	
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
		if (g_map[(int)(initialPosition.x + (directionVec.x * (step)))][(int)(initialPosition.y + (directionVec.y * (step)))] != 0) 
		{
			result.bHit = true;
			result.distance = step;
			result.hitPosition = Vector2D(initialPosition.x + (directionVec.x * step), initialPosition.y + (directionVec.y * step));

			switch (g_map[(int)(initialPosition.x + (directionVec.x * (step)))][(int)(initialPosition.y + (directionVec.y * (step)))]) 
			{
			case 1:
				result.rayColor = { 0,0,0 };
				break;
			case 2:
				result.rayColor = { 0,0,1 };
				break;
			case 3:
				result.rayColor = { 0,1,0 };
				break;
			case 4:
				result.rayColor = { 1,0,0 };
				break;
			case 5:
				result.rayColor = { 1,1,0 };
				break;
			case 6:
				result.rayColor = { 1,0,1 };
				break;
			case 7:
				result.rayColor = { 0,1,1 };
				break;
			case 8:
				result.rayColor = { 1,1,1 }; 
				break;
			case 9:
				result.rayColor = { 0.20f, 0.36, 0.0f };
				break;
			default:
				result.rayColor = { 0,0,0 };
				break;
			}
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
	m_horizonOffset = NormalizeToDivisions(newHorizonOffset); 
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
