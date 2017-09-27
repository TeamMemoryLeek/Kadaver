#include "Vector3.h"

KD_NAMESPACE_BEGIN

// Static const vectors
const Vector3 Vector3::zero = Vector3();
const Vector3 Vector3::posx = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::negx = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::posy = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::negy = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::posz = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::negz = Vector3(0.0f, 0.0f, -1.0f);

Vector3::Vector3(const float& x /* = 0.f */, const float& y /* = 0.f */, 
	const float& z /* = 0.f */)
	: x(x)
	, y(y)
	, z(z)
{
}

Vector3::Vector3(const Vector3& other)
	: x(other.x)
	, y(other.y)
	, z(other.z)
{
}

const Vector3 Vector3::operator + (const Vector3& in) const
{
	return Vector3(x + in.x, y + in.y, z + in.z);

}

const Vector3 Vector3::operator + (const float in) const
{
	return Vector3(x + in, y + in, z + in);

}

void Vector3::operator += (const Vector3& in)
{
	x += in.x;
	y += in.y;
	z += in.z;

}

void Vector3::operator += (const float in)
{
	x += in;
	y += in;
	z += in;

}

const Vector3 Vector3::operator - (const Vector3& in) const
{
	return Vector3(x - in.x, y - in.y, z - in.z);

}

const Vector3 Vector3::operator - (const float in) const
{
	return Vector3(x - in, y - in, z - in);

}

const Vector3 Vector3::operator - () const
{
	return Vector3(-x, -y, -z);
}

void Vector3::operator -= (const Vector3& in)
{
	x -= in.x;
	y -= in.y;
	z -= in.z;

}

void Vector3::operator -= (const float in)
{
	x -= in;
	y -= in;
	z -= in;

}

const Vector3 Vector3::operator * (const Vector3& in) const
{
	return Vector3(x * in.x, y * in.y, z * in.z);

}

const Vector3 Vector3::operator * (const float in) const
{
	return Vector3(x * in, y * in, z * in);

}

void Vector3::operator *= (const Vector3& in)
{
	x *= in.x;
	y *= in.y;
	z *= in.z;

} 

void Vector3::operator *= (const float in)
{
	x *= in;
	y *= in;
	z *= in;

}

const Vector3 Vector3::operator / (const Vector3& in) const
{
	return Vector3(x / in.x, y / in.y, z / in.z);

}

const Vector3 Vector3::operator / (const float in) const
{
	return Vector3(x / in, y / in, z / in);

}

void Vector3::operator /= (const Vector3& in)
{
	x /= in.x;
	y /= in.y;
	z /= in.z;

}

void Vector3::operator /= (const float in)
{
	x /= in;
	y /= in;
	z /= in;

}

bool Vector3::operator == (const Vector3& in) const
{
	return x == in.x && y == in.y && z == in.z;

}

bool Vector3::operator != (const Vector3& in) const
{
	return x != in.x || y != in.y || z != in.z;

}


KD_NAMESPACE_END