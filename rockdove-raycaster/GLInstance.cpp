#include "GLInstance.h"
#include "GLUTCallbacks.h"

GLInstance::GLInstance(int argc, char* argv[]) 
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("rockdove-raycaster by Louise Ramsden");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

void GLInstance::Display() 
{

}

GLInstance::~GLInstance(void) 
{

}