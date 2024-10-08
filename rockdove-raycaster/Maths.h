/*
* Maths.h:
*	Contains all maths functions and concepts
*/

#pragma once
#include <math.h>

#define PI 3.1415927f

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
	float GetMagnitude()
	{
		return sqrtf((this->x * this->x) + (this->y * this->y));
	}
	Vector2D operator*(float const& s1) { return Vector2D(this->x * s1, this->y * s1); }
	Vector2D operator/(float const& s1) { return Vector2D(this->x / s1, this->y / s1); }
	Vector2D operator+(Vector2D const& v1) { return Vector2D(this->x + v1.x, this->y + v1.y); }
	Vector2D operator-(Vector2D const& v1) { return Vector2D(this->x - v1.x, this->y - v1.y); }
	void operator*=(float const& s1) { this->x = this->x * s1; this->y = this->y * s1; }
	void operator/=(float const& s1) { this->x = this->x / s1; this->y = this->y / s1; }
};

inline float DegToRad(float degrees)
{
	return degrees * (PI / 180.0f);
}

inline Vector2D RotToVec(float rot)
{
	return Vector2D(1.0f * cosf(DegToRad(rot + 180)), 1.0f * sinf(DegToRad(rot + 180)));
}

template <typename T>
inline void Swap(T& a, T& b) 
{
	
	a ^= b;
	b ^= a;
	a ^= b;
}