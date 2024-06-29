#include "Raycaster.h"

#include <math.h>


void Raycaster::OGLRender() 
{
	static int a = 0;
	a++;

	glClear(GL_COLOR_BUFFER_BIT);
	float step = 10.0f;
	for (int i = 0; i < (int)step; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f((sinf((float)a / 100.0f) + 1.0f) / 2.0f, 1.0f - ((float)i / step), (cosf((float)a / 100) + 1.0f) / 2.0f);
		glVertex2f(-1.0f + ((float)i / step) * 2.0f, 1.0f);
		glVertex2f(-1.0f + (((float)i + 1.0f) / step) * 2.0f, 1.0f);
		glVertex2f(-1.0f + (((float)i + 1.0f) / step) * 2.0f, -1.0f);
		glVertex2f(-1.0f + ((float)i / step) * 2.0f, -1.0f);
		glEnd();
	}
	glFlush();
}