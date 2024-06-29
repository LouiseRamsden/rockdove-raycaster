#include "Raycaster.h"

#include <math.h>


Raycaster::Raycaster(int rows, int columns) 
{
	m_rows = rows;
	m_columns = columns;
}

void Raycaster::OGLRender() 
{
	static int a = 0;
	a++;

	
	for (int i = 0; i < m_columns; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f((sinf((float)a / 100.0f) + 1.0f) / 2.0f, 1.0f - ((float)i / (float)m_columns), (cosf((float)a / 100) + 1.0f) / 2.0f);
		glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, 1.0f);
		glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, 1.0f);
		glVertex2f(-1.0f + (((float)i + 1.0f) / (float)m_columns) * 2.0f, -1.0f);
		glVertex2f(-1.0f + ((float)i / (float)m_columns) * 2.0f, -1.0f);
		glEnd();
	}
	
}

//Getters and Setters
int Raycaster::GetRows() 
{
	return m_rows;
}
void Raycaster::SetRows(int newRows) 
{
	m_rows = newRows;
}
int	Raycaster::GetColumns() 
{
	return m_columns;
}
void Raycaster::SetColumns(int newColumns) 
{
	m_columns = newColumns;
}