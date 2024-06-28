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
}