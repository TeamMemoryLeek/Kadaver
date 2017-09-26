#pragma once
#include "Common.h"

#include <exception>


// DLL export/import semantics
#if defined(LIB_CORE)
#define KD_CORE_DLL KD_DLL_EXPORT
#else
#define KD_CORE_DLL KD_DLL_IMPORT
#endif

// Temporary definition for knew keyword
#define knew new