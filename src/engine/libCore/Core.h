#pragma once
#include "Common.h"


// DLL export/import semantics
#if defined(LIB_CORE)
#define KD_CORE_DLL KD_DLL_EXPORT
#else
#define KD_CORE_DLL KD_DLL_IMPORT
#endif
