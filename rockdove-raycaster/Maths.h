/*
* Maths.h:
*	Contains all maths functions and concepts
*/

#pragma once

struct Vector2D 
{
	float x, y;

	Vector2D() 
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vector2D(float x, float y) 
	{
		this->x = x;
		this->y = y;
	}
};