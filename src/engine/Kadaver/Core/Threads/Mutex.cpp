#include "Mutex.h"
#include "Kadaver/Core/Engine.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

KD_NAMESPACE_BEGIN

Mutex::Mutex()
	: interlock_(0)
{
}

void Mutex::lock()
{
#ifdef _WIN32
	while (interlock_ == 1 || 
		InterlockedCompareExchange(&interlock_, 1, 0) == 1);
#else
	while (interlock_ == 1 || __sync_lock_test_and_set(&interlock_, 1) == 1);
#endif
}

void Mutex::unlock()
{
	interlock_ = 0;
}

KD_NAMESPACE_END