#include "GLInstance.h"
#include "GLUTCallbacks.h"
#include "Map.h"



GLInstance::GLInstance(int argc, char* argv[]) 
{
	m_renderer = new Raycaster(320, 320);

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1600, 900);
	glutCreateWindow("rockdove-raycaster by Louise Ramsden");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(16, GLUTCallbacks::Timer, 16); //Lock 60(ish) FPS
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutMainLoop();
}

void GLInstance::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
		m_renderer->OGLRender();
	glFlush();
	glutSwapBuffers();
}

void GLInstance::Update() 
{
	glutPostRedisplay();
}

void GLInstance::Keyboard(unsigned char key, int x, int y) 
{

	switch (key) 
	{
	case 'a':
		m_renderer->SetRotation((m_renderer->GetRotation() + 10));
		break;
	case 'd':
		m_renderer->SetRotation((m_renderer->GetRotation() - 10));
		break;
	
	case 'w':
		if (g_map[(int)(m_renderer->GetViewportPosition().x - (RotToVec(m_renderer->GetRotation()).x / 10.0f))][(int)(m_renderer->GetViewportPosition().y - (RotToVec(m_renderer->GetRotation()).y / 10.0f))] == 0)
		{
			m_renderer->SetViewportPosition(m_renderer->GetViewportPosition() - (RotToVec(m_renderer->GetRotation()) / 10));
		}

		break;
	case 's':
		if (g_map[(int)(m_renderer->GetViewportPosition().x + (RotToVec(m_renderer->GetRotation()).x / 10.0f))][(int)(m_renderer->GetViewportPosition().y + (RotToVec(m_renderer->GetRotation()).y / 10.0f))] == 0)
		{
			m_renderer->SetViewportPosition(m_renderer->GetViewportPosition() + (RotToVec(m_renderer->GetRotation()) / 10));
		}

		break;
	//case 'q':
	//	m_renderer->SetHorizonOffset(m_renderer->GetHorizonOffset() + 0.1f);
	//	break;
	//case 'e':
	//	m_renderer->SetHorizonOffset(m_renderer->GetHorizonOffset() - 0.1f);
	//	break;

	}
}

GLInstance::~GLInstance(void) 
{

}