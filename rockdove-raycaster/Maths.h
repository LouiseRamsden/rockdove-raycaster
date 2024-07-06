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
	Vector2D operator*(float const& s1) 
	{
		return Vector2D(this->x * s1, this->y * s1);
	}
	Vector2D operator+(Vector2D const& v1) 
	{
		return Vector2D(this->x + v1.x, this->y + v1.y);
	}
};