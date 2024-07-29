#include "Raycaster.h"

#include "Map.h"

#include <iostream>

Raycaster::Raycaster(int rows, int columns) 
{
	SetRows(rows);
	SetColumns(columns);
	SetHorizonOffset(0.0f);
	SetViewportPosition(Vector2D(1.5, 1.5));
	SetRotation(0.0f);
	SetDarkness(2.0f);
	SetSkyColor(Color3(0.03f, 0.26f, 0.47f));
	SetHorizonColor(Color3(0.98f,0.30f,0.15f));
	SetFloorColor(Color3(0.0f, 0.2f,0.13f));
	
}

//OpenGl 1.0 Rendering function
void Raycaster::OGLRender() 
{
	//Render Sky
	for (int i = 0; i < m_columns; i++)
	{

		glBegin(GL_POLYGON);
			glColor3f(m_skyColor.r / m_darkness,m_skyColor.g / m_darkness,m_skyColor.b / m_darkness); //MAKE VARIABLE
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, 1.0f);
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, 1.0f);
			glColor3f(m_horizonColor.r  /m_darkness, m_horizonColor.g / m_darkness, m_horizonColor.b / m_darkness); //MAKE VARIABLE
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, m_horizonOffset);
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, m_horizonOffset);
		glEnd();
	}
	//Render Floor
	for (int i = 0; i < m_columns; i++)
	{

		glBegin(GL_POLYGON);
			glColor3f(m_floorColor.r / (m_darkness + 1),m_floorColor.g / (m_darkness + 1),m_horizonColor.b / (m_darkness + 1)); //MAKE VARIABLE
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, m_horizonOffset);
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, m_horizonOffset);
			glColor3f(m_floorColor.r / m_darkness, m_floorColor.g / m_darkness, m_floorColor.b / m_darkness); // MAKE VARIABLE
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
			glColor3f(rayHit.rayColor.r/ m_darkness, rayHit.rayColor.g/ m_darkness, rayHit.rayColor.b/ m_darkness);
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, NormalizeToDivisions(m_horizonOffset + heightModifier));
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, NormalizeToDivisions(m_horizonOffset + heightModifier));
			glColor3f(rayHit.rayColor.r / (m_darkness + 2), rayHit.rayColor.g / (m_darkness + 2), rayHit.rayColor.b / (m_darkness + 2)); // Half brightness shadows
			glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, NormalizeToDivisions(m_horizonOffset - heightModifier));
			glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, NormalizeToDivisions(m_horizonOffset - heightModifier));
		glEnd();
	}
	
}




float Raycaster::NormalizeToDivisions(const float value) 
{
	if (value > 1.0f)
	{
		return 1.0f;
	}
	if (value < -1.0f)
	{
		return -1.0f;
	}
	float step = 2.0f / (float)m_rows;
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
	Vector2D xJump = (directionVec / directionVec.x);
	Vector2D yJump = (directionVec / directionVec.y);

	

	for (float step = 0.0f; step < maxDistance; )
	{
		if (g_map[(int)(initialPosition.x + (directionVec.x * (step)))][(int)(initialPosition.y + (directionVec.y * (step)))] != 0)
		{
			result.bHit = true;
			result.distance = step;
			result.hitPosition = Vector2D(initialPosition.x + (directionVec.x * step), initialPosition.y + (directionVec.y * step));

			switch (g_map[(int)(initialPosition.x + (directionVec.x * (step)))][(int)(initialPosition.y + (directionVec.y * (step)))])
			{
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
		//Improvements here!
		step += 0.01f;
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
	while (newRotation > 360.0f) { newRotation -= 360.0f; }
	while (newRotation < 0.0f) { newRotation += 360.0f; }
	m_rotation = newRotation; 
}
//m_fieldOfView
float Raycaster::GetFieldOfView() { return m_fieldOfView; }

//m_darkness
float Raycaster::GetDarkness() { return m_darkness; }
void Raycaster::SetDarkness(const float newDarkness) { m_darkness = newDarkness; }

//m_floorColor
Color3 Raycaster::GetFloorColor() { return m_floorColor; }
void Raycaster::SetFloorColor(Color3 newFloorColor) { m_floorColor = newFloorColor; }

//m_horizonColor
Color3 Raycaster::GetHorizonColor() { return m_horizonColor; }
void Raycaster::SetHorizonColor(Color3 newHorizonColor) { m_horizonColor = newHorizonColor; }

//m_skyColor
Color3 Raycaster::GetSkyColor() { return m_skyColor; }
void Raycaster::SetSkyColor(Color3 newSkyColor) { m_skyColor = newSkyColor;  }
