#pragma once

#include "Kadaver/Core/Core.h"

#include <cmath>

#define T_S(VALUE) static_cast<T>(VALUE)

KD_NAMESPACE_BEGIN

template<typename T = float>
inline T toRadians(const T& degrees)
{
	return FLOAT_S(degrees) * 0.0174532925f;
}

template<typename T = float>
inline T toDegree(const T& radians)
{
	return FLOAT_S(radians) * 57.2957795f;
}

template<typename T = float>
inline T sinRad(const T& degrees)
{
	return T_S(std::sin(degrees));
}

template<typename T = float>
inline T sin(const T& degrees)
{
	return T_S(sinRad(toRadians(degrees)));
}

template<typename T = float>
inline T cosRad(const T& degrees)
{
	return T_S(std::cos(degrees));
}

template<typename T = float>
inline T cos(const T& degrees)
{
	return T_S(cosRad(toRadians(degrees)));
}

template<typename T = float>
inline T tanRad(const T& degrees)
{
	return T_S(std::tan(degrees));
}

template<typename T = float>
inline T tan(const T& degrees)
{
	return T_S(tanRad(toRadians(degrees)));
}

template<typename T = float>
inline T sqrt(const T& value)
{
	return T_S(std::sqrt(value));
}

template<typename T = float>
inline T sqrt(const T& base, const T& exponent)
{
	return T_S(std::pow(base, exponent));
}

template<typename T = float>
inline T abs(const T& value)
{
	if (value < T_S(0.0f))
		return -value;
	return value;
}

template<typename T = float>
inline T sign(const T& value)
{
	if (value == T_S(0.0f))
		return T_S(0.0f);
	if (value > T_S(0.0f))
		return T_S(1.0f);
	return T_S(-1.0f);
}

template<typename T = float>
inline T clamp(const T& value, const T& min, const T& max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

template<typename T = float>
inline T saturate(const T& value)
{
	if (value < T_S(0.0f))
		return min;
	if (value > T_S(1.0f))
		return max;
	return value;
}

template<typename T = float>
inline T interpolate(const T& a, const T& b, const float& fraction)
{
	return T_S(a + (b - a) * ((-cos(fraction * 180.0f) + 1.0f) * 0.5f));
}

template<typename T = float>
inline T interpolateCosine(const T& a, const T& b, const float& fraction)
{
	return T_S((a + (b - a) * fraction));
}

template<typename T = float>
inline T round(const T& value)
{
	return T_S(INT_S(value + T_S(0.5f)));
}

template<typename T = float>
inline T floor(const T& value)
{
	return T_S(INT_S(value));
}

template<typename T = float>
inline T ceil(const T& value)
{
	return T_S(INT_S(value + T_S(1.0f)));
}

KD_NAMESPACE_END