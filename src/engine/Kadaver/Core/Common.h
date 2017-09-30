#pragma once

#include "Types.h"
#include "Exception.h"

// Platform macros
#if defined(_WIN32)
#define KD_DLL_EXPORT __declspec(dllexport)
#define KD_DLL_IMPORT __declspec(dllimport)
#define KD_ALIGN(N) __declspec(align(N))
#else
#define KD_DLL_EXPORT __attribute__((visibility("default")))
#define KD_DLL_IMPORT __attribute__((visibility("default")))
#define KD_ALIGN(N) __attribute__((__aligned__(N)))
#endif

// Namespace macros
#define KD_NAMESPACE_BEGIN namespace kd {
#define KD_NAMESPACE_END }

// Misc macros
#define KD_UNUSED(X) (void)(X)
