#pragma once
class GLInstance;

namespace GLUTCallbacks 
{
	void Init(GLInstance* gl);

	void Display();

	void Timer(int refreshMS);
}