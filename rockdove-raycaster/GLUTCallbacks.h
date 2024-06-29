/*
* GLUTCallbacks:
*	GLUT is old so I have to use a function pointer helper namespace,
*	this is just used so that I can easily link functions to a class
*	and have a much more object oriented approach
*/

#pragma once
class GLInstance;

namespace GLUTCallbacks 
{
	void Init(GLInstance* gl);

	void Display();

	void Timer(int refreshMS);
}