#include "GLUTCallbacks.h"
#include "GLInstance.h"

namespace GLUTCallbacks
{
	namespace
	{
		GLInstance* glInstance = nullptr;
	}

	void Init(GLInstance* gl) 
	{
		glInstance = gl;
	}

	void Display() 
	{
		if (glInstance != nullptr) 
		{
			glInstance->Display();
		}
	}

	void Timer(int refreshMS) 
	{
		if (glInstance != nullptr)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			glInstance->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(refreshMS - updateTime, GLUTCallbacks::Timer, refreshMS);
		}
	}
}