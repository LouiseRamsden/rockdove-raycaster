#include "GLInstance.h"
#include "GLUTCallbacks.h"



GLInstance::GLInstance(int argc, char* argv[]) 
{
	m_renderer = new Raycaster(320, 320);

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
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
}

void GLInstance::Update() 
{
	glutPostRedisplay();
}

void GLInstance::Keyboard(unsigned char key, int x, int y) 
{

	switch (key) 
	{
	case 'q':
		m_renderer->SetRotation((m_renderer->GetRotation() + 10));
		break;
	case 'e':
		m_renderer->SetRotation((m_renderer->GetRotation() - 10));
		break;
	case 'w':
		m_renderer->SetViewportPosition(m_renderer->GetViewportPosition() - (RotToVec(m_renderer->GetRotation())/10));
		break;

	}
}

GLInstance::~GLInstance(void) 
{

}