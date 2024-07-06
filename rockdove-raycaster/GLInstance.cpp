#include "GLInstance.h"
#include "GLUTCallbacks.h"



GLInstance::GLInstance(int argc, char* argv[]) 
{
	m_renderer = new Raycaster(3, 320);

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("rockdove-raycaster by Louise Ramsden");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(16, GLUTCallbacks::Timer, 16); //Lock 60(ish) FPS
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

GLInstance::~GLInstance(void) 
{

}