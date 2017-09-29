#pragma once

#include "Kadaver/Core/Core.h"
#include "Math.hpp"

KD_NAMESPACE_BEGIN

class KD_CORE_DLL Vector3
{
public:
	
	Vector3(const float& x = 0.f, const float& y = 0.f, const float& z = 0.f);
	Vector3(const Vector3& other);

#pragma warning(push)
#pragma warning(disable : 4201)
	union
	{
		struct 
		{
			float x;
			float y;
			float z;
		};
	};
#pragma warning(pop)

	// Static instances
	static const Vector3 zero;

	static const Vector3 posx;
	static const Vector3 negx;

	static const Vector3 posy;
	static const Vector3 negy;

	static const Vector3 posz;
	static const Vector3 negz;

	float length() const
	{
		return sqrt(lengthSquared());
	}

	float lengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	float normalize()
	{
		float magnitude;
		*this = normalized(&magnitude);
		return magnitude;
	}

	const Vector3 normalized(float* outLength = nullptr) const
	{
		Vector3 out;
		const float magnitude = length();

		if (outLength)
			*outLength = magnitude;

		if (magnitude != 0.f)
		{
			out.x = x / magnitude;
			out.y = y / magnitude;
			out.z = z / magnitude;
		}

		return out;
	}

	float dot(const Vector3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	const Vector3 cross(const Vector3& in) const
	{
		return Vector3(y * in.z - in.y * z, z * in.x - in.z * x,
			x * in.y - in.x * y);
	}

	// Addition operators
	const Vector3 operator + (const Vector3& in) const;
	const Vector3 operator + (const float in) const;
	void operator += (const Vector3& in);
	void operator += (const float in);

	// Subtraction operators
	const Vector3 operator - (const Vector3& in) const;
	const Vector3 operator - (const float in) const;
	const Vector3 operator - () const;
	void operator -= (const Vector3& in);
	void operator -= (const float in);

	// Multiplication
	const Vector3 operator * (const Vector3& in) const;
	const Vector3 operator * (const float in) const;
	void operator *= (const Vector3& in);
	void operator *= (const float in);

	// Division operators
	const Vector3 operator / (const Vector3& in) const;
	const Vector3 operator / (const float in) const;
	void operator /= (const Vector3& in);
	void operator /= (const float in);

	// Comparison operators
	bool operator == (const Vector3& in) const;
	bool operator != (const Vector3& in) const;
};

KD_NAMESPACE_END