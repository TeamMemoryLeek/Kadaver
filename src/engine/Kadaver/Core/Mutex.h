#pragma once

#include "Core.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Wrapper class for std::mutex

KD_NAMESPACE_BEGIN

class KD_CORE_DLL Mutex
{
public:
	Mutex();
	void lock();
	void unlock();
private:
	volatile unsigned long long interlock_;
};

KD_NAMESPACE_END