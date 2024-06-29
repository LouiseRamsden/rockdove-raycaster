#include "GLInstance.h"
#include "GLUTCallbacks.h"



GLInstance::GLInstance(int argc, char* argv[]) 
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("rockdove-raycaster by Louise Ramsden");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(16, GLUTCallbacks::Timer, 16); //Lock 60 FPS
	glutMainLoop();
}

void GLInstance::Display() 
{
	renderer->OGLRender();
}

void GLInstance::Update() 
{
	glutPostRedisplay();
}

GLInstance::~GLInstance(void) 
{

}