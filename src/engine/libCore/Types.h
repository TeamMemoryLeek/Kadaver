#pragma once

typedef unsigned int uint;
typedef unsigned char byte;

// Casting macros for some basic types.

#define FLOAT_S(X) static_cast<float>(X);
#define FLOAT_D(X) dynamic_cast<float>(X);
#define FLOAT_R(X) reinterpret_cast<float>(X);
#define FLOAT_C(X) const_cast<float>(X);

#define INT_S(X) static_cast<int>(X);
#define INT_D(X) dynamic_cast<int>(X);
#define INT_R(X) reinterpret_cast<int>(X);
#define INT_C(X) const_cast<int>(X);

#define UINT_S(X) static_cast<uint>(X);
#define UINT_D(X) dynamic_cast<uint>(X);
#define UINT_R(X) reinterpret_cast<uint>(X);
#define UINT_C(X) const_cast<uint>(X);

#define CHAR_S(X) static_cast<char>(X);
#define CHAR_D(X) dynamic_cast<char>(X);
#define CHAR_R(X) reinterpret_cast<char>(X);
#define CHAR_C(X) const_cast<char>(X);

#define BYTE_S(X) static_cast<byte>(X);
#define BYTE_D(X) dynamic_cast<byte>(X);
#define BYTE_R(X) reinterpret_cast<byte>(X);
#define BYTE_C(X) const_cast<byte>(X);