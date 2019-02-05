#pragma once

#include <iostream>

class Vector3
{
public:
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}


	friend float dot(const Vector3 &v1, const Vector3 &v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	 Vector3& operator=(const Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	 Vector3& operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	 Vector3 operator-(const Vector3 &v2) const
	{
		 return Vector3(x - v2.x, y - v2.y, z - v2.z);
	}

	 Vector3 operator*(const float scalar) const
	{
		 return Vector3(x * scalar, y * scalar, z * scalar);
	}

	friend Vector3 operator*(const float scalar, const Vector3 &v) 
	{
		return Vector3(scalar*v.x, scalar*v.y, scalar*v.z);
	}

	friend std::ostream& operator <<(std::ostream &stream, const Vector3 &v)
	{
		return stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		
	}

	friend Vector3 ProjectOn(const Vector3 &v1, const Vector3 &v2)
	{
		float dotProduct = dot(v1,v2);
		Vector3 v = dotProduct * v2;
		float normsq = dot(v2, v2);

		return v * (1.0f / normsq);
	}
};
